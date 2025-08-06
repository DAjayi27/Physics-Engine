//
// Created by AJYDAN on 01/05/2025.
//

#include "collision.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "core/vector.h"
#include "physics/rigid_body.h"

#define NO_OF_COLLISIONS 3
typedef bool (*CollisionFunc)(Entity* a, Entity* b);

static CollisionFunc dispatch_table[NO_OF_COLLISIONS][NO_OF_COLLISIONS];

/**
 * @brief Performs axis-aligned bounding box collision detection
 * @param first_shape First entity
 * @param second_shape Second entity
 * @return True if AABB collision detected, false otherwise
 */
bool aabb_collision(Entity* first_shape, Entity* second_shape) {
    if (first_shape->shape->get_collision_type() != AABB_COLLISION || 
        second_shape->shape->get_collision_type() != AABB_COLLISION) {
        fprintf(stderr, "Non rectangle collider shape passed to rectangle on rectangle collider");
        return false;
    }

	Rectangle* first_rect = ((Rectangle*)first_shape->shape.get());
	Rectangle* second_rect = ((Rectangle*)second_shape->shape.get());

    return (first_shape->get_position().x < second_shape->get_position().x + second_rect->get_width() &&
            first_shape->get_position().x + first_rect->get_width() > second_shape->get_position().x &&
            first_shape->get_position().y < second_shape->get_position().y + second_rect->get_height() &&
            first_shape->get_position().y + first_rect->get_height() > second_shape->get_position().y);
}

/**
 * @brief Performs circle-to-circle collision detection
 * @param first_shape First entity
 * @param second_shape Second entity
 * @return True if circle collision detected, false otherwise
 */
bool circle_collision(Entity* first_shape, Entity* second_shape) {
  if (first_shape->shape->get_collision_type() != CIRCLE_COLLISION || 
    second_shape->shape->get_collision_type() != CIRCLE_COLLISION) {
    fprintf(stderr, "Non circle collider shape passed to circle on circle collider");
    return false;
  }

	Circle* first_circle =  (Circle*)first_shape->shape.get();
	Circle* second_circle =  (Circle*)second_shape->shape.get();

  float distance_sqr = vector_distance_squared(first_shape->get_position(), second_shape->get_position());
  float radius_sum = first_circle->get_radius() + second_circle->get_radius();

    return distance_sqr <= (radius_sum * radius_sum);
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
 * @return true if a collision has occurred, and false if it hasn't
 *
 ***/
extern bool circle_aabb_collision(Entity* first_shape, Entity* second_shape) {

 // determine which one is the circle and which one is the rectangle.

 // make sure they don't have the same collisions
 if (first_shape->shape->get_collision_type() == second_shape->shape->get_collision_type()) {
  fprintf(stderr, "Warning: Circle on AABB Collision function, passed shapes of same collision type.\n Please ensure the two shapes are not the same type.\n");
  return false;
 }

  if ((first_shape->shape->get_collision_type() != AABB_COLLISION && 
        first_shape->shape->get_collision_type() != CIRCLE_COLLISION) ||
      (second_shape->shape->get_collision_type() != AABB_COLLISION && 
        second_shape->shape->get_collision_type() != CIRCLE_COLLISION)) {
      fprintf(stderr, "Non rectangle or circle shape passed to rectangle on circle collider");
      return false;
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
      return false;
  }


 // check for collision

 float rect_min_x = rect->get_position().x;
 float rect_max_x = rect->get_position().x + ((Rectangle*)rect->shape.get())->get_width();

 float rect_min_y = rect->get_position().y;
 float rect_max_y = rect->get_position().y + ((Rectangle*)rect->shape.get())->get_height();

    float rec_closest_x = fminf(fmaxf(rect_min_x, circle->get_position().x), rect_max_x);
    float rec_closest_y = fminf(fmaxf(rect_min_y, circle->get_position().y), rect_max_y);

    Vector2D point = {rec_closest_x, rec_closest_y};
    float distance_sqr = vector_distance_squared(point, circle->get_position());
    float radius = dynamic_cast<Circle*>(circle->shape.get())->get_radius();

    return distance_sqr <= (radius * radius);
}


/**
 * @brief Checks if two entities are colliding
 * @param first_shape First entity
 * @param second_shape Second entity
 * @return True if entities are colliding, false otherwise
 */
bool is_colliding(Entity* first_shape, Entity* second_shape) {
    CollisionFunc func = dispatch_table[first_shape->shape->get_collision_type()][second_shape->shape->get_collision_type()];

    if (func) {
        return func(first_shape, second_shape);
    } else {
        fprintf(stderr, "Unsupported collision type combination\n");
        return false;
    }
}

/**
 * @brief Handles collision response between two entities
 * @param entity_a First entity
 * @param entity_b Second entity
 */
void handle_collision(Entity* entity_a, Entity* entity_b) {

	((Rigid_Body*)entity_a->physics.get())->set_affected_by_gravity(false);
	((Rigid_Body*)entity_b->physics.get())->set_affected_by_gravity(false);


	if (!entity_a->is_static()) {
		entity_a->physics->set_position_y(entity_a->physics->get_position().y - 100);
	}


	if (!entity_b->is_static()) {
		entity_b->physics->set_position_y(entity_b->physics->get_position().y - 100);
	}

	//
	// if (entity_a->physics->is_static() || entity_b->physics->is_static() ) {
	// 	Entity* dynamic_entity = nullptr;
	//
	// 	if (entity_a->physics->is_static()) {
	// 		dynamic_entity = entity_b;
	// 	}else {
	// 		dynamic_entity = entity_a;
	// 	}
	//
	// 	((Rigid_Body*)dynamic_entity->physics.get())->set_affected_by_gravity(false);
	// }else {
	// 	return;
	// }




}