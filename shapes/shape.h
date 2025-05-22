//
// Created by AJYDAN on 02/05/2025.
//

#ifndef SHAPE_H
#define SHAPE_H

typedef struct Shape Shape;

#include <stdbool.h>
#include "circle.h"
#include "rectangle.h"
#include "collision/collision_types.h"

struct Shape {
    Collision_Type collision_type;
    bool has_collider;
    union {
        Circle circle;
        Rectangle rect;
    };
    Vector_2D position;
};


extern Shape create_circle(float x,float y ,float radius,SDL_Color color,bool has_collision);
extern Shape create_rect(float x,float ,float width,float height,SDL_Color color,bool has_collision);
extern float get_area(Shape* shape);

#endif //SHAPE_H
