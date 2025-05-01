//
// Created by AJYDAN on 01/05/2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <stdbool.h>

#include "collision/collision.h"
#include "core/vector.h"
#include <SDL3/SDL.h>

typedef struct Rectangle {
    Collision_Type collision_type;
    bool has_collider;
    Vector_2D position;
    SDL_Color color;
    float width;
    float height;
} Rectangle;

extern Rectangle* new_rectangle(Collision_Type collision_type, float x,float ,float width,float height,SDL_Color color);

extern bool destroy_rect(Rectangle* rectangle);

extern bool render_rect(Rectangle* rectangle , SDL_Renderer* renderer,SDL_Texture* texture);

#endif //RECTANGLE_H
