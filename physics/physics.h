#pragma once

#include "core/entity.h"
#include "physics/physics_component.h"
#include "physics/rigid_body.h"

/**
 * @brief Updates the physics simulation for an entity
 * @param entity The entity to update
 * @param delta_time Time elapsed since last frame
 */
void update_physics(Entity* entity, float delta_time);

// Legacy compatibility
#define update_gravity_physics update_physics
