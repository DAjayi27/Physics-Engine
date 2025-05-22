//
// Created by AJYDAN on 02/05/2025.
//



#include <stdlib.h>

#include "circle.h"



extern Circle* new_circle(float x,float y ,float radius,SDL_Color color) {


    Circle* new_circle  =  calloc(1,sizeof(Circle));

    new_circle->position.x = x;
    new_circle->position.y = y;

    new_circle->color = color;

    new_circle->radius = radius;

    return new_circle;

}






