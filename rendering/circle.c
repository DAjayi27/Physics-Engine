//
// Created by AJYDAN on 02/05/2025.
//

#include "circle.h"

#include <stdlib.h>

#include "shape.h"


extern Circle* new_circle(float x,float y ,float radius,SDL_Color color) {


    Circle* new_circle  =  calloc(1,sizeof(Circle));

    new_circle->position.x = x;
    new_circle->position.y = y;

    new_circle->color = color;

    new_circle->radius = radius;

    return new_circle;

}


extern void render_circle_bresenham(Shape* shape,SDL_Renderer *renderer, bool is_fill) {

    Circle* circle = &shape->circle;

    circle->position = shape->position;

    SDL_SetRenderDrawColor(renderer,circle->color.r,circle->color.g,circle->color.b,circle->color.a);

    int cx = circle->position.x;
    int cy = circle->position.y;
    int radius = circle->radius;

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


extern void render_circle_mid_point(Circle* circle,SDL_Renderer *renderer, bool is_fill) {

    int cx = circle->position.x;
    int cy = circle->position.y;
    int radius = circle->radius;

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




