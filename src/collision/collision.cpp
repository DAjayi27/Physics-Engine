//
// Created by AJYDAN on 01/05/2025.
//

#include "collision.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stl_algo.h>

#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "core/vector.h"
#include "physics/rigid_body.h"



CollisionManager::CollisionManager() {
	this->init_dispatch_table();
}


/**
 * @brief Performs axis-aligned bounding box collision detection
 * @param first_shape First entity
 * @param second_shape Second entity
 * @return True if AABB collision detected, false otherwise
 */
 Vector2D CollisionManager::aabb_collision(Entity* first_shape, Entity* second_shape) {

	if (first_shape->shape->get_collision_type() != AABB_COLLISION ||second_shape->shape->get_collision_type() != AABB_COLLISION) {
		fprintf(stderr, "Non rectangle collider shape passed to rectangle on rectangle collider");
		return Vector2D{0,0};
	}

	Rectangle* first_rect = ((Rectangle*)first_shape->shape.get());
	Rectangle* second_rect = ((Rectangle*)second_shape->shape.get());

	// Check collision
	bool is_colliding =  (
		first_shape->get_position().x < second_shape->get_position().x + second_rect->get_width() &&
		first_shape->get_position().x + first_rect->get_width() > second_shape->get_position().x &&
		first_shape->get_position().y < second_shape->get_position().y + second_rect->get_height() &&
		first_shape->get_position().y + first_rect->get_height() > second_shape->get_position().y
	);

	if (is_colliding) {
		// Centers of rectangles
		Vector2D c1(first_shape->get_position().x + first_rect->get_width()/2,first_shape->get_position().y + first_rect->get_height()/2);
		Vector2D c2(second_shape->get_position().x + second_rect->get_width()/2,second_shape->get_position().y + second_rect->get_height()/2);

		// Difference vector
		float dx = c2.x - c1.x;
		float dy = c2.y - c1.y;

		// Half-size sums
		float px = (first_rect->get_width()/2 + second_rect->get_width()/2) - std::abs(dx);
		float py = (first_rect->get_height()/2 + second_rect->get_height()/2) - std::abs(dy);

		// Axis of least penetration → collision normal
		Vector2D collision_normal;
		if (px < py) {
			collision_normal = Vector2D((dx < 0) ? -1 : 1, 0); // horizontal normal
		} else {
			collision_normal = Vector2D(0, (dy > 0) ? 1 : -1);// vertical normal
		}

		// collision_normal now points from first rectangle to second rectangle
		return collision_normal;
	}

	return Vector2D{0,0}; // No collision
}

/**
 * @brief Performs circle-to-circle collision detection
 * @param first_shape First entity
 * @param second_shape Second entity
 * @return True if circle collision detected, false otherwise
 */
 Vector2D CollisionManager::circle_collision(Entity* first_shape, Entity* second_shape) {
  if (first_shape->shape->get_collision_type() != CIRCLE_COLLISION || 
    second_shape->shape->get_collision_type() != CIRCLE_COLLISION) {
    fprintf(stderr, "Non circle collider shape passed to circle on circle collider");
    return Vector2D{0,0};
  }

	Circle* first_circle =  (Circle*)first_shape->shape.get();
	Circle* second_circle =  (Circle*)second_shape->shape.get();

  float distance_sqr = vector_distance_squared(first_shape->get_position(), second_shape->get_position());
  float radius_sum = first_circle->get_radius() + second_circle->get_radius();

	if (distance_sqr <= (radius_sum * radius_sum)) {

		Vector2D collision_vector = {first_shape->get_position().x - second_shape->get_position().x ,
			first_shape->get_position().y - second_shape->get_position().y};

		return vector_normalize(collision_vector);
	}else {
		return Vector2D{0,0};
	}
}

/**
 * This function handles circle on rectangle object collisions
 *
 *@link https://www.gamedevelopment.blog/collision-detection-circles-rectangles-and-polygons/ (Read to understand the logic)
 *@link https://www.jeffreythompson.org/collision-detection/circle-rect.php (Read to understand the logic)
 *
 * @param first_shape The first shape being compared
 * @param second_shape the second shape being compared
 *
 * @return a normalised collision vector between the two entities if a collision occurs or a zero vector if no collision occurs
 *
 ***/
 Vector2D CollisionManager::circle_aabb_collision(Entity* first_shape, Entity* second_shape) {

	// determine which one is the circle and which one is the rectangle.

	// make sure they don't have the same collisions
	if (first_shape->shape->get_collision_type() == second_shape->shape->get_collision_type()) {
	fprintf(stderr, "Warning: Circle on AABB Collision function, passed shapes of same collision type.\n Please ensure the two shapes are not the same type.\n");
	return Vector2D{0,0};
	}

	if ((first_shape->shape->get_collision_type() != AABB_COLLISION &&
	      first_shape->shape->get_collision_type() != CIRCLE_COLLISION) ||
	    (second_shape->shape->get_collision_type() != AABB_COLLISION &&
	      second_shape->shape->get_collision_type() != CIRCLE_COLLISION)) {
	    fprintf(stderr, "Non rectangle or circle shape passed to rectangle on circle collider");
	    return Vector2D{0,0};
	}

	Entity* circle;
	Entity* rect;

	if (first_shape->shape->get_collision_type() == CIRCLE_COLLISION) {
	    circle = first_shape;
	    rect = second_shape;
	} else if (second_shape->shape->get_collision_type() == CIRCLE_COLLISION) {
	    circle = second_shape;
	    rect = first_shape;
	} else {
		return Vector2D{0,0};;
	}


	// check for collision

	float rect_min_x = rect->get_position().x;
	float rect_max_x = rect->get_position().x + ((Rectangle*)rect->shape.get())->get_width();

	float rect_min_y = rect->get_position().y;
	float rect_max_y = rect->get_position().y + ((Rectangle*)rect->shape.get())->get_height();

	float rec_closest_x = std::clamp(circle->get_position().x, rect_min_x, rect_max_x);
	float rec_closest_y = std::clamp(circle->get_position().y, rect_min_y, rect_max_y);


	Vector2D point = {rec_closest_x, rec_closest_y};
	float distance_sqr = vector_distance_squared(point, circle->get_position());
	float radius = dynamic_cast<Circle*>(circle->shape.get())->get_radius();

	bool is_colliding =  distance_sqr <= (radius * radius);

	if (is_colliding) {
		Vector2D collision_vector = {rec_closest_x - circle->get_position().x , rec_closest_y - circle->get_position().y};
		Vector2D collision_normal = vector_normalize(collision_vector);
		return  collision_normal;
	}else{
		return Vector2D{0,0};;
	}
}


/**
 * @brief Checks if two entities are colliding
 * @param first_shape First entity
 * @param second_shape Second entity
 * @return True if entities are colliding, false otherwise
 */
Vector2D CollisionManager::is_colliding(Entity* first_shape, Entity* second_shape) {
    CollisionFunc func = dispatch_table[first_shape->shape->get_collision_type()][second_shape->shape->get_collision_type()];

    if (func) {
        return func(first_shape, second_shape);
    } else {
        fprintf(stderr, "Unsupported collision type combination\n");
        return Vector2D{0,0};
    }
}

/**
 * @brief Handles collision response between two entities
 * @param entity_a First entity
 * @param entity_b Second entity
 */
void CollisionManager::handle_collision(Entity* entity_a, Entity* entity_b,Vector2D collision_normal) {
	Rigid_Body* bodyA = static_cast<Rigid_Body*>(entity_a->physics.get());
	Rigid_Body* bodyB = static_cast<Rigid_Body*>(entity_b->physics.get());

	// Step 1: Relative velocity
	Vector2D rv = vector_subtract(bodyB->get_velocity(), bodyA->get_velocity());

	// Step 2: Relative velocity along the normal
	float velAlongNormal = vector_dot(rv, collision_normal);

	if (velAlongNormal > 0) {
		return;
	}

	// Step 3: Coefficient of restitution
	float e = std::min(bodyA->get_restitution(), bodyB->get_restitution());

	// Step 4: Compute inverse masses safely
	float invMassA = (bodyA->get_mass() > 0.0f) ? 1.0f / bodyA->get_mass() : 0.0f;
	float invMassB = (bodyB->get_mass() > 0.0f) ? 1.0f / bodyB->get_mass() : 0.0f;

	float invMassSum = invMassA + invMassB;
	if (invMassSum == 0.0f) return; // both bodies are static, no impulse

	// Step 5: Impulse scalar
	float j = -(1.0f + e) * velAlongNormal / invMassSum;

	// Step 6: Impulse vector
	Vector2D impulse = vector_scale(collision_normal, j);

	// Step 7: Apply impulse
	bodyA->set_velocity(vector_subtract(bodyA->get_velocity(), vector_scale(impulse, invMassA)));
	bodyB->set_velocity(vector_add(bodyB->get_velocity(), vector_scale(impulse, invMassB)));
}


// Helper to initialize the table
void CollisionManager::init_dispatch_table() {

 	dispatch_table[AABB_COLLISION][AABB_COLLISION] = CollisionManager::aabb_collision;
 	dispatch_table[CIRCLE_COLLISION][CIRCLE_COLLISION] = CollisionManager::circle_collision;
 	dispatch_table[CIRCLE_COLLISION][AABB_COLLISION] = CollisionManager::circle_aabb_collision;
 	dispatch_table[AABB_COLLISION][CIRCLE_COLLISION] = CollisionManager::circle_aabb_collision;
}

void CollisionManager::checkCollisions(vector<unique_ptr<Entity>>& entities) {



	for (size_t i = 0; i < entities.size(); ++i) {
		for (size_t j = i + 1; j < entities.size(); ++j) {

			auto& entity_a = entities[i];
			auto& entity_b = entities[j];

			Vector2D collision_normal = this->is_colliding( entity_a.get(), entity_b.get() );

			if ( collision_normal.x != 0 || collision_normal.y != 0   ) {

				this->handle_collision(entity_a.get(), entity_b.get(),collision_normal);

				currently_colliding_entities.insert(this->generatePairing(entity_a->entity_id , entity_b->entity_id));
				continue;
			}


			handleCollisionExit(entity_a,entity_b);

		}
	}
}

void CollisionManager::update_collision_tracker() {

	if (!this->currently_colliding_entities.empty()) {
		this->prev_colliding_entities  = this->currently_colliding_entities;
		this->currently_colliding_entities.clear();
	}

}


uint64_t CollisionManager::generatePairing (uint32_t first_id ,  uint32_t second_id) {
	return (uint64_t)std::min(first_id,second_id) << 32 | std::max(first_id,second_id);
}

void CollisionManager::handleCollisionExit(unique_ptr<Entity>& entity_a , unique_ptr<Entity>& entity_b ) {

	uint64_t paired_id = this->generatePairing(entity_a->entity_id , entity_b->entity_id);

	if (prev_colliding_entities.contains(paired_id)) {
		((Rigid_Body*)entity_a->physics.get())->set_affected_by_gravity(true);
		((Rigid_Body*)entity_b->physics.get())->set_affected_by_gravity(true);
	}
}






