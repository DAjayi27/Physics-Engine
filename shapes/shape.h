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
#include <SDL3/SDL.h>

typedef enum shape_type{
    NO_SHAPE,
    CIRCLE,
    RECTANGLE,
    POLYGON,
    TRIANGLE
}shape_type;

struct Shape {
    Collision_Type collision_type;
    bool has_collider;
    union {
        Circle circle;
        Rectangle rect;
    };

};


extern Shape create_circle(float radius,bool has_collision);
extern Shape create_rect(float width,float height,bool has_collision);
extern float get_area(Shape* shape);

#endif //SHAPE_H
