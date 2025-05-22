//
// Created by AJYDAN on 02/05/2025.
//

#include "entity.h"

extern Entity create_entity(Shape shape, Physics_Component physics_component) {

    Entity new_entity = {shape,physics_component};

    return new_entity;
}