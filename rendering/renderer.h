//
// Created by AJYDAN on 21/05/2025.
//

#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <SDL3/SDL_render.h>
#include "core/entity.h"

void render_rect(Entity* entity , SDL_Renderer* renderer,SDL_Texture* texture,bool is_fill);
extern void render_circle_bresenham(Entity* entity,SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill);

extern void render_circle_mid_point(Entity* entity,SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill);

extern void render_entity(Entity* entity, SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill);

extern void initialise_render_dispatch();

#endif //SHAPE_RENDERER_H
