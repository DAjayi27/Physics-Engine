#pragma once

#include "core/entity.h"
#include <memory>
#include <functional>

constexpr int NO_OF_COLLISIONS = 3;
using CollisionFunc = std::function<Vector2D(Entity*, Entity*)>;

class CollisionManager {

private:
	inline static CollisionFunc dispatch_table[NO_OF_COLLISIONS][NO_OF_COLLISIONS] = {};
	static Vector2D aabb_collision(Entity* entity_a, Entity* entity_b);
	static Vector2D circle_aabb_collision(Entity* first_shape, Entity* second_shape);
	static Vector2D circle_collision(Entity* first_shape, Entity* second_shape);




public:
	// CollisionManager();
	static Vector2D is_colliding(Entity* entity_a, Entity* entity_b);
	static void handle_collision(Entity* entity_a, Entity* entity_b , Vector2D collision_normal);
	static void init_dispatch_table();

};






