//
// Created by AJYDAN on 21/05/2025.
//

#include "physics.h"
#include "physics_component.h"
#include "core/vector.h"
#include <math.h>

/**
 * @brief Updates the physics simulation for an entity
 * @param entity The entity to update
 * @param delta_time Time elapsed since last frame
 */
void update_physics(Entity* entity, float delta_time) {
    if (!entity || !entity->physics) {
        return;
    }

    // Each physics component handles its own update logic
    entity->physics->update(delta_time, entity->shape->get_area());
}


