//
// Created by AJYDAN on 02/05/2025.
//

#include "physics_component.h"

#include <math.h>
#include <stdio.h>


extern void update_physics(Entity* shape, float dt) {
    if (!shape->physics) return;

    switch (shape->physics->type) {

        case PHYSICS_RIGID_BODY:
            Rigid_Body* rb = &shape->physics->rigid_body;

            if (rb->is_static) return;


            float velocity_y = rb->velocity.y;
            float area = get_area(shape->shape);

            // Air drag: F_drag = -0.5 * ρ * A * v * |v|
            float drag_force = -0.5f * 1.293f * area * velocity_y * fabsf(velocity_y)*0.47;

            // Gravity
            float gravitational_force = rb->mass * 9.81;

            // Net force
            float total_force = drag_force + gravitational_force;

            // Acceleration = F / m
            float actual_acceleration = total_force / rb->mass;

            // Position update: Δx = v₀ * dt + 0.5 * a * dt²
            float new_position_offset = rb->velocity.y * dt + 0.5f * actual_acceleration * dt * dt;

            // Velocity update: v = v₀ + a * dt
            rb->velocity.y += actual_acceleration * dt;

            Vector_2D new = {0, new_position_offset};
            shape->shape->position = vector_add(shape->shape->position, new);
            printf("v=%.2f drag=%.2f gravity=%.2f accel=%.2f\n",
            rb->velocity.y, drag_force, gravitational_force, actual_acceleration);


        break;


        case PHYSICS_KINEMATIC:
            // No physics updates, user controls position
                break;

        case PHYSICS_PARTICLE:
            // Simple gravity with potential drag
                break;

        case PHYSICS_NONE:
        default:
            break;
    }
}
