#pragma once

#include "core/entity.h"
#include <memory>

/**
 * @brief Initializes the collision detection system
 */
void initialize_collision_system();

/**
 * @brief Checks if two entities are colliding
 * @param entity_a First entity
 * @param entity_b Second entity
 * @return True if entities are colliding, false otherwise
 */
Vector2D is_colliding(Entity* entity_a, Entity* entity_b);

/**
 * @brief Performs axis-aligned bounding box collision detection
 * @param entity_a First entity
 * @param entity_b Second entity
 * @return True if AABB collision detected, false otherwise
 */
Vector2D aabb_collision(Entity* entity_a, Entity* entity_b);

/**
 * @brief Handles collision response between two entities
 * @param entity_a First entity
 * @param entity_b Second entity
 */
void handle_collision(Entity* entity_a, Entity* entity_b , Vector2D collision_normal);

// Legacy compatibility
#define initialise_collision_dispatch initialize_collision_system
