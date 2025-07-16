//
// Created by AJYDAN on 21/05/2025.
//

#pragma once

#include <SDL3/SDL_render.h>
#include "core/entity.h"

/**
 * @brief Rendering system namespace
 */
namespace Renderer {
    /**
     * @brief Renders an entity to the screen
     * @param entity Entity to render
     * @param renderer SDL renderer
     * @param texture Optional texture (can be nullptr)
     * @param fill Whether to fill the shape or just outline
     */
    void render_entity(Entity* entity, SDL_Renderer* renderer, 
                      SDL_Texture* texture, bool fill);
    
    /**
     * @brief Initializes the rendering system
     */
    void initialize_render_system();
    
    // Legacy compatibility
    #define initialise_render_dispatch initialize_render_system
}



