//
// Created by AJYDAN on 02/05/2025.
//

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

typedef enum Physics_Type Physics_Type;

typedef struct Physics_Component Physics_Component;

#include "rigid_body.h"
#include "rendering/shape.h"
#include "core/entity.h"
#include  "core/vector.h"

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
} ;

extern void update_gravity_physics(Entity* shape, float dt);

#endif //PHYSICS_COMPONENT_H
