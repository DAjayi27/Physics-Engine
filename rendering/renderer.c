//
// Created by AJYDAN on 21/05/2025.
//

#include "renderer.h"

void sdl_from_rect(Entity* entity, SDL_FRect* dest_rect) {

    Rectangle* rectangle = &entity->shape.rect;

    dest_rect->x = entity->position.x;
    dest_rect->y = entity->position.y;

    dest_rect->w = rectangle->width;
    dest_rect->h = rectangle->height;
}


bool render_rect(Entity* rectangle , SDL_Renderer* renderer,SDL_Texture* texture) {

    SDL_FRect dest_rect = {0,0,0,0};
    sdl_from_rect(rectangle,&dest_rect);

    if (rectangle == NULL || renderer == NULL) {
        return false;
    }

    if (texture != NULL) {
        return SDL_RenderTexture(renderer,texture,NULL,&dest_rect);
    }else {
        SDL_SetRenderDrawColor(renderer,rectangle->color.r,rectangle->color.g,rectangle->color.b,rectangle->color.a);
        return SDL_RenderFillRect(renderer,&dest_rect);
    }

    return false;

}


extern void render_circle_bresenham(Entity* entity,SDL_Renderer *renderer, bool is_fill) {

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


extern void render_circle_mid_point(Entity* entity,SDL_Renderer *renderer, bool is_fill) {

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
