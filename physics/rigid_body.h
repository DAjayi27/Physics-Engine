//
// Created by AJYDAN on 02/05/2025.
//

#ifndef RIGID_BODY_H
#define RIGID_BODY_H

typedef struct Rigid_Body Rigid_Body;

#include <stdbool.h>
#include "core/vector.h"


struct Rigid_Body {

    Vector_2D velocity;
    Vector_2D acceleration;
    float mass;
    float restitution;
    bool affected_by_gravity;
    bool is_static;

};


#endif //RIGID_BODY_H
