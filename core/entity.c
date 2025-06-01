//
// Created by AJYDAN on 02/05/2025.
//

#include "entity.h"

extern Entity create_entity(Shape shape, Physics_Component physics_component) {

    Entity new_entity = {shape,physics_component};

    return new_entity;
}

//  CIRCLE CONSTRUCTORS


/***
 * Constructor For A New Circle entity with no physics attached
 */
extern Entity create_circle_entity(float x,float y,float radius,bool has_collision,SDL_Color color) {

    Entity new_entity;

    Shape new_shape = create_circle(radius,has_collision);

    new_entity.shape = new_shape;
    new_entity.position.x = x;
    new_entity.position.y = y;
    new_entity.color = color;

    return new_entity;
}

/***
 * Constructor For A New Circle entity with full physics attached
 */
extern Entity create_circle_physics_entity(float x,float y,float radius,SDL_Color color,Physics_Type physics_type, Vector_2D velocity , Vector_2D acceleration , float mass) {

    bool has_collision =  true;

    if (physics_type == PHYSICS_NONE) {
        has_collision = false;
    }

    Entity new_entity = create_circle_entity(x,y,radius,has_collision,color);

    new_entity.physics = create_physics_component(physics_type,velocity,acceleration,mass);

    return new_entity;

}

/***
 * Constructor For A New Circle entity with physics attached, but acceleration and velocity set to zero
 */
extern Entity create_circle_zero_entity(float x,float y,float radius,SDL_Color color,Physics_Type physics_type, float mass) {

    Vector_2D zero_vector = {0,0};

    Entity new_entity =  create_circle_physics_entity(x,y,radius,color,physics_type,zero_vector,zero_vector,mass);

    return new_entity;
}


//  RECTANGLE CONSTRUCTORS

/***
 * Constructor For A New Rectangle entity with no physics attached
 */
extern Entity create_rect_entity(float x,float y,float width,float height, bool has_collision,SDL_Color color) {

    Entity new_entity;

    Shape new_shape = create_rect(width,height,has_collision);


    new_entity.shape = new_shape;
    new_entity.position.x = x;
    new_entity.position.y = y;
    new_entity.color = color;

    return new_entity;
}

/***
 * Constructor For A New Rectangle entity with full physics attached
 */
extern Entity create_rect_physics_entity(float x,float y,float width,float height,SDL_Color color,Physics_Type physics_type, Vector_2D velocity , Vector_2D acceleration , float mass) {

    bool has_collision =  true;

    if (physics_type == PHYSICS_NONE) {
        has_collision = false;
    }

    Entity new_entity = create_rect_entity(x,y,width,height,has_collision,color);

    new_entity.physics = create_physics_component(physics_type,velocity,acceleration,mass);

    return new_entity;

}

/***
 * Constructor For A New Rectangle entity with physics attached, but acceleration and velocity set to zero
 */
extern Entity create_rect_zero_entity(float x,float y,float width,float height,SDL_Color color,Physics_Type physics_type,float mass) {

    Vector_2D zero_vector = {0,0};

    Entity new_entity = create_rect_physics_entity(x,y,width,height,color,physics_type,zero_vector,zero_vector,mass);

    return new_entity;
}

extern void set_mass(Entity entity,float mass) {
}

extern void set_acceleration(Entity entity,Vector_2D acceleration) {

}

extern void set_velocity(Entity entity,Vector_2D velocity) {

}
