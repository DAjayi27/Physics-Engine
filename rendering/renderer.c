//
// Created by AJYDAN on 21/05/2025.
//

#include "renderer.h"

#include <stdio.h>

#define RENDER_OPTIONS 2

typedef void (*RenderFunc)(Entity* entity , SDL_Renderer* renderer,SDL_Texture* texture,bool is_fill);

static RenderFunc render_dispatch_table[RENDER_OPTIONS];

/**
 * @brief Converts an Entity's rectangle shape to an SDL_FRect.
 *
 * This function extracts the rectangle shape from the given entity and fills the provided
 * SDL_FRect structure with the position and size data.
 *
 * @param entity Pointer to the Entity containing the rectangle shape.
 * @param dest_rect Pointer to the SDL_FRect to be filled.
 */
void sdl_from_rect(Entity* entity, SDL_FRect* dest_rect) {

    Rectangle* rectangle = &entity->shape.rect;

    dest_rect->x = entity->position.x;
    dest_rect->y = entity->position.y;

    dest_rect->w = rectangle->width;
    dest_rect->h = rectangle->height;
}

/**
 * @brief Renders a rectangle entity using SDL.
 *
 * This function renders the given rectangle entity using the provided SDL_Renderer.
 * If a texture is provided, it renders the texture; otherwise, it fills the rectangle
 * with the entity's color.
 *
 * @param entity Pointer to the Entity representing the rectangle.
 * @param renderer Pointer to the SDL_Renderer used for rendering.
 * @param texture Optional SDL_Texture to render. If NULL, a filled rectangle is drawn.
 * @param is_fill Boolean indicating whether the rectangle should be filled.
 */
void render_rect(Entity* entity , SDL_Renderer* renderer,SDL_Texture* texture,bool is_fill) {

    SDL_FRect dest_rect = {0,0,0,0};
    sdl_from_rect(entity,&dest_rect);

    if (entity == NULL || renderer == NULL) {
      exit(1000);
    }

    if (texture != NULL) {
         SDL_RenderTexture(renderer,texture,NULL,&dest_rect);
    }else {
        SDL_SetRenderDrawColor(renderer,entity->color.r,entity->color.g,entity->color.b,entity->color.a);
         SDL_RenderFillRect(renderer,&dest_rect);
    }

}

/**
 * @brief Renders a circle entity using the Bresenham algorithm.
 *
 * This function draws a circle (optionally filled) at the entity's position using the
 * Bresenham circle drawing algorithm.
 *
 * @param entity Pointer to the Entity representing the circle.
 * @param renderer Pointer to the SDL_Renderer used for rendering.
 * @param is_fill If true, the circle is filled; otherwise, only the outline is drawn.
 */
extern void render_circle_bresenham(Entity* entity,SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill) {

    Circle* circle = &entity->shape.circle;

    SDL_SetRenderDrawColor(renderer,entity->color.r,entity->color.g,entity->color.b,entity->color.a);

    int cx = entity->position.x;
    int cy = entity->position.y;
    int radius = entity->shape.circle.radius;

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

        if (is_fill) {

            SDL_RenderLine(renderer,cx + x,cy + y,cx - x,cy + y);
            SDL_RenderLine(renderer,cx + x,cy - y,cx - x,cy - y);
            SDL_RenderLine(renderer,cx + y,cy + x,cx - y,cy + x);
            SDL_RenderLine(renderer,cx + y,cy - x,cx - y,cy - x);

        }

        if (d < 0) {
            d = d + (2 * (3 + 2*y) );
        } else {
            d = d + (2 * (5 - 2*x + 2*y));
            x--;
        }
        y++;


    }
}

/**
 * @brief Renders a circle entity using the Midpoint algorithm.
 *
 * This function draws a circle (optionally filled) at the entity's position using the
 * Midpoint circle drawing algorithm.
 *
 * @param entity Pointer to the Entity representing the circle.
 * @param renderer Pointer to the SDL_Renderer used for rendering.
 * @param is_fill If true, the circle is filled; otherwise, only the outline is drawn.
 */
extern void render_circle_mid_point(Entity* entity,SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill) {

    SDL_SetRenderDrawColor(renderer,entity->color.r,entity->color.g,entity->color.b,entity->color.a);

    int cx = entity->position.x;
    int cy = entity->position.y;
    int radius = entity->shape.circle.radius;

    int x = 0;
    int y = -radius;
    int d = -radius + 0.25;

    while (x < -y) {

        if (d > 0) {
            y++;
            d = d + (2 * (x + y) + 1 );
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

        if (is_fill) {

            SDL_RenderLine(renderer,cx + x,cy + y,cx - x,cy + y);
            SDL_RenderLine(renderer,cx + x,cy - y,cx - x,cy - y);
            SDL_RenderLine(renderer,cx + y,cy + x,cx - y,cy + x);
            SDL_RenderLine(renderer,cx + y,cy - x,cx - y,cy - x);

        }



        x++;
    }
}

/**
     * @brief Initializes the dispatch table with rendering functions.
     *
     * This function sets up the dispatch table by associating specific rendering functions
     * with collision types. It ensures that each entry in the table is initialized to NULL
     * before assigning the appropriate rendering functions.
     */
    extern void initialise_render_dispatch() {

        for (int i = 0; i < RENDER_OPTIONS; ++i) {
            render_dispatch_table[RENDER_OPTIONS] = NULL;
        }

        render_dispatch_table[AABB_COLLISION] = render_rect;
        render_dispatch_table[CIRCLE_COLLISION] = render_circle_bresenham;

    }

    /**
     * @brief Renders an entity using the appropriate rendering function.
     *
     * This function determines the rendering function to use based on the entity's collision type
     * and invokes it. If the collision type is unsupported, an error message is printed to stderr.
     *
     * @param entity Pointer to the Entity to be rendered.
     * @param renderer Pointer to the SDL_Renderer used for rendering.
     * @param texture Optional SDL_Texture to render. If NULL, a default rendering method is used.
     * @param is_fill Boolean indicating whether the entity should be filled during rendering.
     */
    extern void render_entity(Entity* entity, SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill) {

        RenderFunc func =  render_dispatch_table[entity->shape.collision_type];

        if (func) {
            func(entity, renderer,texture,is_fill);
        }
        else {
            fprintf(stderr, "Unsupported collision type combination\n");
        }

    }