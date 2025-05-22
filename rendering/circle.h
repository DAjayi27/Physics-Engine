//
// Created by AJYDAN on 02/05/2025.
//

#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct Circle Circle;
#include <SDL3/SDL_pixels.h>
#include "core/vector.h"
#include "circle.h"




struct Circle {
    Vector_2D position;
    SDL_Color color;
    float radius;
};

#include "shape.h"
#include <SDL3/SDL_render.h>


extern Circle* new_circle(float x,float y,float radius,SDL_Color color);

extern bool destroy_circle(Circle* rectangle);

extern void render_circle_bresenham(Shape* shape,SDL_Renderer *renderer, bool is_fill);

extern void render_circle_mid_point(Circle* circle,SDL_Renderer *renderer, bool is_fill);

#endif //CIRCLE_H
