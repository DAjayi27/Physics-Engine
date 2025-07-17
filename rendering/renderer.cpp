//
// Created by AJYDAN on 21/05/2025.
//

#include "renderer.h"

#include <stdio.h>

#include "shapes/circle.h"
#include "shapes/rectangle.h"

#define RENDER_OPTIONS 2

namespace Renderer {

	typedef void (*RenderFunc)(Entity* entity, SDL_Renderer* renderer, SDL_Texture* texture, bool fill);

	static RenderFunc render_dispatch_table[RENDER_OPTIONS];

	/**
	 * @brief Converts an Entity's rectangle shape to an SDL_FRect
	 * @param entity Pointer to the Entity containing the rectangle shape
	 * @param dest_rect Pointer to the SDL_FRect to be filled
	 */
	void sdl_from_rect(Entity* entity, SDL_FRect* dest_rect) {

	    Rectangle* rectangle = dynamic_cast<Rectangle*>(entity->shape.get());

	    dest_rect->x = entity->physics->get_position().x;
	    dest_rect->y = entity->physics->get_position().y;

	    dest_rect->w = rectangle->get_width();
	    dest_rect->h = rectangle->get_height();
	}

	/**
	 * @brief Renders a rectangle entity using SDL
	 * @param entity Pointer to the Entity representing the rectangle
	 * @param renderer Pointer to the SDL_Renderer used for rendering
	 * @param texture Optional SDL_Texture to render. If NULL, a filled rectangle is drawn
	 * @param fill Boolean indicating whether the rectangle should be filled
	 */
	void render_rect(Entity* entity, SDL_Renderer* renderer, SDL_Texture* texture, bool fill) {

	    SDL_FRect dest_rect = {0, 0, 0, 0};
	    sdl_from_rect(entity, &dest_rect);

	    if (entity == NULL || renderer == NULL) {
	      exit(1000);
	    }

	    if (texture != NULL) {
	         SDL_RenderTexture(renderer, texture, NULL, &dest_rect);
	    }else {
	        SDL_SetRenderDrawColor(renderer, entity->color.r, entity->color.g, entity->color.b, entity->color.a);
	         SDL_RenderFillRect(renderer, &dest_rect);
	    }

	}

	/**
	 * @brief Renders a circle entity using the Bresenham algorithm
	 * @param entity Pointer to the Entity representing the circle
	 * @param renderer Pointer to the SDL_Renderer used for rendering
	 * @param texture Optional texture (unused for circles)
	 * @param fill If true, the circle is filled; otherwise, only the outline is drawn
	 */
	void render_circle_bresenham(Entity* entity, SDL_Renderer* renderer, SDL_Texture* texture, bool fill) {

		if (entity->shape->get_type() != ShapeType::CIRCLE) {
			exit(100);
		}



	    SDL_SetRenderDrawColor(renderer, entity->color.r, entity->color.g, entity->color.b, entity->color.a);

	    int cx = entity->physics->get_position().x;
	    int cy = entity->physics->get_position().y;
	    int radius = dynamic_cast<Circle*>(entity->shape.get())->get_radius();

	    int x = radius;
	    int y = 0;
	    int d = 3 - 2 * radius;

	    while (x >= y) {
	        SDL_RenderPoint(renderer, cx + x, cy + y);
	        SDL_RenderPoint(renderer, cx - x, cy + y);
	        SDL_RenderPoint(renderer, cx + x, cy - y);
	        SDL_RenderPoint(renderer, cx - x, cy - y);
	        SDL_RenderPoint(renderer, cx + y, cy + x);
	        SDL_RenderPoint(renderer, cx - y, cy + x);
	        SDL_RenderPoint(renderer, cx + y, cy - x);
	        SDL_RenderPoint(renderer, cx - y, cy - x);

	        if (fill) {
	            SDL_RenderLine(renderer, cx + x, cy + y, cx - x, cy + y);
	            SDL_RenderLine(renderer, cx + x, cy - y, cx - x, cy - y);
	            SDL_RenderLine(renderer, cx + y, cy + x, cx - y, cy + x);
	            SDL_RenderLine(renderer, cx + y, cy - x, cx - y, cy - x);
	        }

	        if (d < 0) {
	            d = d + (2 * (3 + 2 * y));
	        } else {
	            d = d + (2 * (5 - 2 * x + 2 * y));
	            x--;
	        }
	        y++;


	    }
	}

	/**
	 * @brief Renders a circle entity using the Midpoint algorithm
	 * @param entity Pointer to the Entity representing the circle
	 * @param renderer Pointer to the SDL_Renderer used for rendering
	 * @param texture Optional texture (unused for circles)
	 * @param fill If true, the circle is filled; otherwise, only the outline is drawn
	 */
	void render_circle_midpoint(Entity* entity, SDL_Renderer* renderer, SDL_Texture* texture, bool fill) {
		SDL_SetRenderDrawColor(renderer, entity->color.r, entity->color.g, entity->color.b, entity->color.a);

		if (entity->shape->get_type() != ShapeType::CIRCLE) {
			exit(100);
		}

		int cx = entity->physics->get_position().x;
		int cy = entity->physics->get_position().y;
		int radius = dynamic_cast<Circle*>(entity->shape.get())->get_radius();

		int x = 0;
		int y = -radius;
		int d = -radius + 0.25;

		while (x < -y) {
			if (d > 0) {
				y++;
				d = d + (2 * (x + y) + 1);
			} else {
				d = d + 2 * x + 1;
			}

			SDL_RenderPoint(renderer, cx + x, cy + y);
			SDL_RenderPoint(renderer, cx - x, cy + y);
			SDL_RenderPoint(renderer, cx + x, cy - y);
			SDL_RenderPoint(renderer, cx - x, cy - y);
			SDL_RenderPoint(renderer, cx + y, cy + x);
			SDL_RenderPoint(renderer, cx - y, cy + x);
			SDL_RenderPoint(renderer, cx + y, cy - x);
			SDL_RenderPoint(renderer, cx - y, cy - x);

			if (fill) {
				SDL_RenderLine(renderer, cx + x, cy + y, cx - x, cy + y);
				SDL_RenderLine(renderer, cx + x, cy - y, cx - x, cy - y);
				SDL_RenderLine(renderer, cx + y, cy + x, cx - y, cy + x);
				SDL_RenderLine(renderer, cx + y, cy - x, cx - y, cy - x);
			}

			x++;
		}
	}

	/**
	 * @brief Initializes the rendering system
	 */
	void initialize_render_system() {

	        for (int i = 0; i < RENDER_OPTIONS; ++i) {
	            render_dispatch_table[i] = nullptr;
	        }

	        render_dispatch_table[AABB_COLLISION] = render_rect;
	        render_dispatch_table[CIRCLE_COLLISION] = render_circle_bresenham;
	}

  /**
   * @brief Renders an entity using the appropriate rendering function
   * @param entity Pointer to the Entity to be rendered
   * @param renderer Pointer to the SDL_Renderer used for rendering
   * @param texture Optional SDL_Texture to render. If NULL, a default rendering method is used
   * @param fill Boolean indicating whether the entity should be filled during rendering
   */
	void render_entity(Entity* entity, SDL_Renderer* renderer, SDL_Texture* texture, bool fill) {

	  RenderFunc func = render_dispatch_table[entity->shape->get_collision_type()];

	  if (func) {
	      func(entity, renderer, texture, fill);
	  }
	  else {
	      fprintf(stderr, "Unsupported collision type combination\n");
	  }
	}
}
