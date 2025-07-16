//
// Created by AJYDAN on 01/05/2025.
//

#include "collision.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "shapes/circle.h"
#include "shapes/rectangle.h"


#define NO_OF_COLLISIONS 3
typedef bool (*CollisionFunc)(Entity* a, Entity* b);

static CollisionFunc dispatch_table[NO_OF_COLLISIONS][NO_OF_COLLISIONS];





/**
 * This function handles rectangle on rectangle object collisions
 *
 * It uses Axis Aligned Bounding Boxes to decide the collisions
 *
 * @param first_shape The first shape being compared
 * @param second_shape the second shape being compared
 *
 * @return true if a collision has occurred, and false if it hasn't
 *
 ***/
extern bool aabb_collision(Entity* first_shape, Entity* second_shape) {

   if (first_shape->shape->get_collision_type() != AABB_COLLISION || second_shape->shape->get_collision_type() != AABB_COLLISION) {
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
 * This function handles circle on circle object collisions

 *
 * @param first_shape The first shape being compared
 * @param second_shape the second shape being compared
 *
 * @return true if a collision has occurred, and false if it hasn't
 *
 ***/
extern bool circle_collision(Entity* first_shape, Entity* second_shape) {

  // Check for proper types

  if (first_shape->shape->get_collision_type() != CIRCLE_COLLISION || second_shape->shape->get_collision_type() != CIRCLE_COLLISION) {
   fprintf(stderr, "Non circle collider shape passed to circle on circle collider");
   return false;
  }

	Circle* first_circle =  (Circle*)first_shape->shape.get();
	Circle* second_circle =  (Circle*)second_shape->shape.get();

  float distance_sqr = vector_dist_sqr(first_shape->get_position(),second_shape->get_position());

  float radius_sum = first_circle->get_radius() + second_circle->get_radius();

  if (distance_sqr <= (radius_sum*radius_sum)) {
   return true;
  }
  else {
   return false;
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


 if ((first_shape->shape->get_collision_type() != AABB_COLLISION && first_shape ->shape->get_collision_type() != CIRCLE_COLLISION)  ||
  (second_shape->shape->get_collision_type() != AABB_COLLISION && second_shape->shape->get_collision_type() != CIRCLE_COLLISION)
 ) {
  fprintf(stderr, "Non rectangle or circle shape passed to rectangle on circle collider");
  return false;
 }

 Entity* circle;
 Entity* rect;

 if (first_shape->shape->get_collision_type() == CIRCLE_COLLISION) {
   circle = first_shape;
   rect = second_shape;
 }
 else if (second_shape->shape->get_collision_type() == CIRCLE_COLLISION) {
  circle = second_shape;
  rect = first_shape;
 }
 else {
  return false;
 }


 // check for collision

 float rect_min_x = rect->get_position().x;
 float rect_max_x = rect->get_position().x + ((Rectangle*)rect->shape.get())->get_width();

 float rect_min_y = rect->get_position().y;
 float rect_max_y = rect->get_position().y + ((Rectangle*)rect->shape.get())->get_height();


 float rec_closest_x = fminf(fmaxf(rect_min_x,circle->get_position().x),rect_max_x);
 float rec_closest_y = fminf(fmaxf(rect_min_y,circle->get_position().y),rect_max_y);

 Vector_2D point = {rec_closest_x,rec_closest_y};

 float distance_sqr = vector_dist_sqr(point,circle->get_position());

	float radius = ((Circle*)circle->shape.get())->get_radius();

 if (distance_sqr <= std::pow(radius,2)) {
  return true;
 }
 else {
  return false;
 }
}

/**
 * @brief Initializes the collision dispatch table.
 *
 * This function sets up a 2D dispatch table for handling collisions between different types of shapes.
 * The dispatch table is used to determine which collision function to call based on the types of the
 * two shapes involved in the collision.
 *
 * The table is initialized with NULL values for unsupported collision type combinations, and specific
 * collision functions are assigned for supported combinations.
 *
 * @note The dispatch table is a static 2D array of function pointers, where each entry corresponds to
 * a specific pair of collision types.
 */
extern void initialise_collision_dispatch() {

 for (int i = 0; i < NO_OF_COLLISIONS; ++i) {
  for (int j = 0; j < NO_OF_COLLISIONS; ++j) {

   dispatch_table[NO_OF_COLLISIONS][NO_OF_COLLISIONS] = NULL;

  }
 }

 // Initializing the dispatch table based on the collision types
 dispatch_table[AABB_COLLISION][AABB_COLLISION] = aabb_collision;
 dispatch_table[CIRCLE_COLLISION][CIRCLE_COLLISION] = circle_collision;
 dispatch_table[CIRCLE_COLLISION][AABB_COLLISION] = circle_aabb_collision;
 dispatch_table[AABB_COLLISION][CIRCLE_COLLISION] = circle_aabb_collision;


}



/***
 * This is the main dispatch function for handling collisions in the engine
 * The system makes use of a 2d dispatch table for handling which methods are called,
 * based on which of the 2 shapes are colliding.
 *
 *  The dispatch table, stores the function potions in a 2D array.
 *
 * @param first_shape The first shape being compared
 * @param second_shape the second shape being compared
 *
 * @return true if a collision has occurred, and false if it hasn't
 *
 */

extern bool is_colliding (Entity* first_shape , Entity* second_shape) {

 CollisionFunc func = dispatch_table[first_shape->shape->get_collision_type()][second_shape->shape->get_collision_type()];

 if (func) {
  return func(first_shape,second_shape);
 }
 else {
  fprintf(stderr, "Unsupported collision type combination\n");
  return false;
 }


}


extern void handle_collision(Entity* entity_a , Entity* entity_b) {

  // Only handle collision if exactly one entity is kinematic
  if ((entity_a->physics->get_type() == PHYSICS_KINEMATIC && entity_b->physics->get_type() != PHYSICS_KINEMATIC) ||
      (entity_a->physics->get_type() != PHYSICS_KINEMATIC && entity_b->physics->get_type() == PHYSICS_KINEMATIC))
  {
     Entity* stop_entity;
    if (entity_a->physics->get_type() != PHYSICS_KINEMATIC) {

      stop_entity = entity_a;

    }else {
      stop_entity = entity_b;
    }

   Vector_2D zero = {0,0};
   stop_entity->physics->set_velocity(zero);

  }


}