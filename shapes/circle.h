//
// Created by AJYDAN on 02/05/2025.
//

#ifndef CIRCLE_H
#define CIRCLE_H

typedef struct Circle Circle;
#include <SDL3/SDL_pixels.h>





struct Circle {
    float radius;
};




extern Circle* new_circle(float radius,SDL_Color color);

extern bool destroy_circle(Circle* rectangle);



#endif //CIRCLE_H
