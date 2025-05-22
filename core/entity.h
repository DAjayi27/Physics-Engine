//
// Created by AJYDAN on 02/05/2025.
//

#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity Entity;

#include "physics/physics_component.h"
#include "shapes/shape.h"


struct Entity {
    Shape shape;
    Physics_Component physics;
};

extern Entity create_entity(Shape shape, Physics_Component physics_component);



#endif //ENTITY_H
