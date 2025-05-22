//
// Created by AJYDAN on 01/05/2025.
//

#include "rectangle.h"

#include <stdlib.h>



Rectangle* new_rectangle(float x,float y,float width,float height,SDL_Color color) {

    Rectangle* new_rect  =  calloc(1,sizeof(Rectangle));

    new_rect->position.x = x;
    new_rect->position.y = y;

    new_rect->color = color;

    new_rect->width = width;
    new_rect->height = height;

    return new_rect;
}


bool destroy_rect(Rectangle* rectangle) {

    free(rectangle);

    return true;
}




