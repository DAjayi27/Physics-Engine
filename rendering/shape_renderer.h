//
// Created by AJYDAN on 21/05/2025.
//

#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <SDL3/SDL_render.h>
#include "core/entity.h"

extern bool render_rect(Rectangle* rectangle , SDL_Renderer* renderer,SDL_Texture* texture);
extern void render_circle_bresenham(Entity* entity,SDL_Renderer *renderer, bool is_fill);

extern void render_circle_mid_point(Circle* circle,SDL_Renderer *renderer, bool is_fill);

#endif //SHAPE_RENDERER_H
