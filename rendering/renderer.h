//
// Created by AJYDAN on 21/05/2025.
//

#pragma once

#include <SDL3/SDL_render.h>
#include "core/entity.h"

namespace Renderer {
	void render_entity(Entity* entity, SDL_Renderer *renderer,SDL_Texture* texture, bool is_fill);
	void initialise_render_dispatch();
}



