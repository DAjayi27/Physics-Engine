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
    Vector_2D position;
    SDL_Color color;
};

extern Entity create_entity(Shape shape, Physics_Component physics_component);



// Constructors For Rectangle Entities
extern Entity create_rect_entity(float x,float y,float width,float height,bool has_collision,SDL_Color color);
extern Entity create_rect_physics_entity(float x,float y,float width,float height,SDL_Color color,Physics_Type physics_type, Vector_2D velocity , Vector_2D acceleration , float mass);
extern Entity create_rect_zero_entity(float x,float y,float width,float height,SDL_Color color,Physics_Type physics_type,float mass);

// Constructors For Circle Entities
extern Entity create_circle_entity(float x,float y,float radius,bool has_collision,SDL_Color color);
extern Entity create_circle_physics_entity(float x,float y,float radius,SDL_Color color,Physics_Type physics_type, Vector_2D velocity , Vector_2D acceleration , float mass);
extern Entity create_circle_zero_entity(float x,float y,float radius,SDL_Color color,Physics_Type physics_type, float mass);

extern void set_mass(Entity entity,float mass);

extern void set_acceleration(Entity entity,Vector_2D acceleration);

extern void set_velocity(Entity entity,Vector_2D velocity);



#endif //ENTITY_H
