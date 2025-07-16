//
// Created by AJYDAN on 21/05/2025.
//

#include "physics.h"

#include "physics_component.h"

#include <math.h>


/**
 *
 * At each frame, drag or gravity physics for each object is being updated.
 * It uses simple drag physics to preform frame time calculations.
 * read (https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/drageq.html) or
 * watch (https://www.youtube.com/watch?v=ZgqJ5wQF944&ab_channel=Debunked) for more info
 *
 * @param entity the shape or entity being updated
 * @param dt id the frame update time (time delay between each drawn frame)
 *
 * NOTE: there is a conversion btw px and meters at a rate of 100px = 1m
 *
 ***/
void handle_rigid_body_gravity(Entity* entity, float dt, Rigid_Body* rb) {
    float velocity_y = rb->get_velocity().y;
    float area = entity->shape->get_area();

    // Air drag: F_drag = -0.5 * ρ * A * v * |v|
    float drag_force = -0.5f * 1.293f * area * velocity_y * fabsf(velocity_y)*0.47;

    // Gravity
    float gravitational_force = rb->get_mass() * 4.5;

    // Net force
    float total_force = drag_force + gravitational_force;

    // Acceleration = F / m
    float actual_acceleration = total_force / rb->get_mass();

    // Position update: Δx = v₀ * dt + 0.5 * a * dt²
    float new_position_offset = rb->get_velocity().y * dt + 0.5f * actual_acceleration * dt * dt;

    // Velocity update: v = v₀ + a * dt
    rb->set_velocity_y(rb->get_velocity().y + actual_acceleration * dt);

    Vector_2D new_velocity = {0, new_position_offset*100};

    entity->set_position(vector_add(entity->get_position(), new_velocity));
}


extern void update_gravity_physics(Entity* entity, float dt) {


    switch (entity->physics->get_type()) {

        case PHYSICS_RIGID_BODY: {

        	Physics_Component* physics_component = entity->physics.get();

        	if (physics_component->get_is_static()) {
        		return;
        	}
        	handle_rigid_body_gravity(entity, dt, static_cast<Rigid_Body*>(physics_component));

        }break;

        case PHYSICS_KINEMATIC: {

        }break;

        case PHYSICS_PARTICLE: {

        }break;

        case PHYSICS_NONE:
        default: {

        }break;
    }
}


