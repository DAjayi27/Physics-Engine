//
// Created by AJYDAN on 02/05/2025.
//

#include "shape.h"

#include <math.h>

extern Shape create_circle(float radius,bool has_collision) {
    Shape new_circle;

    if (!has_collision) {
        new_circle.has_collider = false;
        new_circle.collision_type = NONE;
    }
    else {
        new_circle.has_collider = true;
        new_circle.collision_type = CIRCLE_COLLISION;
    }
        new_circle.circle.radius = radius;
    return new_circle;
}


extern Shape create_rect(float width,float height,bool has_collision){

    Shape new_rect;

    if (!has_collision) {
        new_rect.has_collider = false;
        new_rect.collision_type = NONE;
    }
    else {
        new_rect.has_collider = true;
        new_rect.collision_type = AABB_COLLISION;
    }
    new_rect.rect.width = width;
    new_rect.rect.height = height;

    return new_rect;
}

/**
 *
 * @param shape The shape being calculated
 * @return the area of the shape in meters (100 px = 1m)
 */
extern float get_area(Shape* shape) {

    switch (shape->collision_type) {

    case CIRCLE_COLLISION:
        return M_PI * ((shape->circle.radius/100)*(shape->circle.radius/100));

    }



}