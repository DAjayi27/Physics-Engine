//
// Created by AJYDAN on 01/05/2025.
//

#ifndef COLLISION_H
#define COLLISION_H
#include <stdbool.h>
#include "shapes/shape.h"
#include "core/entity.h"



extern void initialise_collision_dispatch();

extern bool is_colliding (Entity* first_shape , Entity* second_shape);

extern bool aabb_collision(Entity* first_shape , Entity* second_shape);

#endif //COLLISION_H
