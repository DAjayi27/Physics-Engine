//
// Created by AJYDAN on 01/05/2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

typedef struct Rectangle Rectangle;

#include <stdbool.h>
#include "core/vector.h"
#include <SDL3/SDL.h>

struct Rectangle {
    Vector_2D position;
    SDL_Color color;
    float width;
    float height;
};

// extern Rectangle* new_rectangle(float x,float ,float width,float height,SDL_Color color);

// extern bool destroy_rect(Rectangle* rectangle);



#endif //RECTANGLE_H
