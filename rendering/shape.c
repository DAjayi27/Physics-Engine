//
// Created by AJYDAN on 02/05/2025.
//

#include "shape.h"

extern Shape create_circle(float x,float y ,float radius,SDL_Color color,bool has_collision) {
    Shape new_circle;

    if (!has_collision) {
        new_circle.has_collider = false;
        new_circle.collision_type = NONE;
    }
    else {
        new_circle.has_collider = true;
        new_circle.collision_type = CIRCLE_COLLISION;
    }

    new_circle.circle.position.x = x;
    new_circle.circle.position.y = y;

    new_circle.circle.color = color;

    new_circle.circle.radius = radius;

    return new_circle;

}


extern Shape create_rect(float x,float y ,float width,float height,SDL_Color color,bool has_collision) {

    Shape new_rect;

    if (!has_collision) {
        new_rect.has_collider = false;
        new_rect.collision_type = NONE;
    }
    else {
        new_rect.has_collider = true;
        new_rect.collision_type = AABB_COLLISION;
    }

    new_rect.rect.position.x = x;
    new_rect.rect.position.y = y;

    new_rect.rect.color = color;

    new_rect.rect.width = width;
    new_rect.rect.height = height;

    return new_rect;


}