#pragma once

#include "core/entity.h"
#include <memory>
#include <functional>
#include <set>

constexpr int NO_OF_COLLISIONS = 3;
using CollisionFunc = std::function<Vector2D(Entity*, Entity*)>;
using std::vector;
using std::unique_ptr;
using std::set;

class CollisionManager {

private:
	CollisionFunc dispatch_table[NO_OF_COLLISIONS][NO_OF_COLLISIONS] = {};
	set<uint64_t> currently_colliding_entities;
	set<uint64_t> prev_colliding_entities;
	static Vector2D aabb_collision(Entity* entity_a, Entity* entity_b);
	static Vector2D circle_aabb_collision(Entity* first_shape, Entity* second_shape);
	static Vector2D circle_collision(Entity* first_shape, Entity* second_shape);
	void update_collision_tracker();
	uint64_t generatePairing (uint32_t first_id ,  uint32_t second_id);
	void handleCollisionExit(unique_ptr<Entity>& entity_a , unique_ptr<Entity>& entity_b );
	void seperate_entities(Entity* entity_a, Entity* entity_b,Vector2D collision_normal);



public:
	CollisionManager();
	Vector2D is_colliding(Entity* entity_a, Entity* entity_b);
	void handle_collision(Entity* entity_a, Entity* entity_b , Vector2D collision_normal);
	void init_dispatch_table();
	void checkCollisions(vector<unique_ptr<Entity>>& entities);

};






