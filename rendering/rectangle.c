//
// Created by AJYDAN on 01/05/2025.
//

#include "rectangle.h"

#include <stdlib.h>

void sdl_from_rect(Rectangle* rectangle, SDL_FRect* dest_rect) {


    dest_rect->x = rectangle->position.x;
    dest_rect->y = rectangle->position.y;

    dest_rect->w = rectangle->width;
    dest_rect->h = rectangle->height;
}

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

bool render_rect(Rectangle* rectangle , SDL_Renderer* renderer,SDL_Texture* texture) {

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


