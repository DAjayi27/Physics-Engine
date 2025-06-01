//
// Created by AJYDAN on 01/05/2025.
//

#include "collision.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>



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

   if (first_shape->shape.collision_type != AABB_COLLISION || second_shape->shape.collision_type != AABB_COLLISION) {
    fprintf(stderr, "Non rectangle collider shape passed to rectangle on rectangle collider");
    return false;
   }

    return (first_shape->position.x < second_shape->position.x + second_shape->shape.rect.width &&
            first_shape->position.x + first_shape->shape.rect.width > second_shape->position.x &&
            first_shape->position.y < second_shape->position.y + second_shape->shape.rect.height &&
            first_shape->position.y + first_shape->shape.rect.height > second_shape->position.y);
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

  if (first_shape->shape.collision_type != CIRCLE_COLLISION || second_shape->shape.collision_type != CIRCLE_COLLISION) {
   fprintf(stderr, "Non circle collider shape passed to circle on circle collider");
   return false;
  }

  float distance_sqr = vector_dist_sqr(first_shape->position,second_shape->position);

  float radius_sum = first_shape->shape.circle.radius + second_shape->shape.circle.radius;

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
 if (first_shape->shape.collision_type == second_shape->shape.collision_type) {
  fprintf(stderr, "Warning: Circle on AABB Collision function, passed shapes of same collision type.\n Please ensure the two shapes are not the same type.\n");
  return false;
 }


 if ((first_shape->shape.collision_type != AABB_COLLISION && first_shape ->shape.collision_type != CIRCLE_COLLISION)  ||
  (second_shape->shape.collision_type != AABB_COLLISION && second_shape->shape.collision_type != CIRCLE_COLLISION)
 ) {
  fprintf(stderr, "Non rectangle or circle shape passed to rectangle on circle collider");
  return false;
 }

 Entity* circle;
 Entity* rect;

 if (first_shape->shape.collision_type == CIRCLE_COLLISION) {
   circle = first_shape;
   rect = second_shape;
 }
 else if (second_shape->shape.collision_type == CIRCLE_COLLISION) {
  circle = second_shape;
  rect = first_shape;
 }
 else {
  return false;
 }


 // check for collision

 float rect_min_x = rect->position.x;
 float rect_max_x = rect->position.x + rect->shape.rect.width;

 float rect_min_y = rect->position.y;
 float rect_max_y = rect->position.y + rect->shape.rect.height;


 float rec_closest_x = fminf(fmaxf(rect_min_x,circle->position.x),rect_max_x);
 float rec_closest_y = fminf(fmaxf(rect_min_y,circle->position.y),rect_max_y);

 Vector_2D point = {rec_closest_x,rec_closest_y};

 float distance_sqr = vector_dist_sqr(point,circle->position);


 if (distance_sqr <= (circle->shape.circle.radius*circle->shape.circle.radius)) {
  return true;
 }
 else {
  return false;
 }
}


extern void initialise_dispatch() {

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

 CollisionFunc func = dispatch_table[first_shape->shape.collision_type][second_shape->shape.collision_type];

 if (func) {
  return func(first_shape,second_shape);
 }
 else {
  fprintf(stderr, "Unsupported collision type combination\n");
  return false;
 }


}
