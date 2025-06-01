
#include "physics_component.h"

#include <string.h>


extern Physics_Component create_physics_component(Physics_Type type, Vector_2D velocity , Vector_2D acceleration , float mass) {

    Physics_Component new_component;
    Rigid_Body new_rigid_body;

    new_rigid_body.acceleration = acceleration;
    new_rigid_body.mass = mass;
    new_rigid_body.velocity = velocity;
    new_component.type = type;

    if (type == PHYSICS_NONE) {
        new_rigid_body.is_static = true;
        new_rigid_body.affected_by_gravity = false;
        new_rigid_body.restitution = 0;
    }else {
        new_rigid_body.is_static = false;
        new_rigid_body.affected_by_gravity = true;
    }

    new_rigid_body.restitution = 0;
    new_component.rigid_body = new_rigid_body;

    return  new_component;
}
