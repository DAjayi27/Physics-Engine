//
// Created by AJYDAN on 02/05/2025.
//

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

typedef enum Physics_Type Physics_Type;

typedef struct Physics_Component Physics_Component;

#include "rigid_body.h"


enum Physics_Type{
    PHYSICS_NONE,
    PHYSICS_RIGID_BODY,
    PHYSICS_KINEMATIC,
    PHYSICS_PARTICLE
};

struct Physics_Component{
    Physics_Type type;
    union {
        Rigid_Body rigid_body;
    };
};

extern Physics_Component create_physics_component(Physics_Type type, Vector_2D velocity , Vector_2D acceleration , float mass);




#endif //PHYSICS_COMPONENT_H
