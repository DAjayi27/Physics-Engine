//
// Created by AJYDAN on 01/05/2025.
//

#ifndef COLLISION_H
#define COLLISION_H
#include <stdbool.h>
#include "shapes/shape.h"




extern void initialise_dispatch();

extern bool is_colliding (Shape* first_shape , Shape* second_shape);

extern bool aabb_collision(Shape* first_shape , Shape* second_shape);

#endif //COLLISION_H
