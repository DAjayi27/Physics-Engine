//
// Created by AJYDAN on 01/07/2025.
//

#include "kinematic.h"
#include "core/vector.h"
#include <math.h>

Kinematic::Kinematic() {
    // Default constructor - all values are initialized in the header
}

Kinematic::Kinematic(float mass, Vector2D velocity, Vector2D acceleration, 
                     bool is_static, bool affected_by_gravity,float ppm) {
    this->mass = mass;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->static_object = is_static;
    this->affected_by_gravity = affected_by_gravity;
		this->pixelPerMeter = ppm;
}

void Kinematic::update(float delta_time, float area) {
    if (static_object) {
        return;
    }

    if (affected_by_gravity) {
        update_gravity_physics(delta_time, area);
    }
}

/**
 * @brief Updates gravity physics with drag forces for kinematic bodies
 * 
 * Same physics calculations as Rigid_Body but for kinematic objects.
 * At each frame, drag or gravity physics for each object is being updated.
 * It uses simple drag physics to perform frame time calculations.
 *
 * @param delta_time The frame update time (time delay between each drawn frame)
 * @param area The area of the object for drag calculations
 *
 * NOTE: There is a conversion between pixels and meters at a rate of 100px = 1m
 */
void Kinematic::update_gravity_physics(float delta_time, float area) {
    if (static_object || !affected_by_gravity) {
        return;
    }

    float velocity_y = velocity.y;

    // Air drag: F_drag = -0.5 * ρ * A * v * |v|
    float drag_force = -0.5f * 1.293f * area * velocity_y * fabsf(velocity_y) * 0.47f;

    // Gravity
    float gravitational_force = mass * 4.5f;

    // Net force
    float total_force = drag_force + gravitational_force;

    // Acceleration = F / m
    float actual_acceleration = total_force / mass;

    // Position update: Δx = v₀ * dt + 0.5 * a * dt²
    float new_position_offset = velocity.y * delta_time + 0.5f * actual_acceleration * delta_time * delta_time;

    // Velocity update: v = v₀ + a * dt
    velocity.y += actual_acceleration * delta_time;

    // Update position
    Vector2D new_velocity = {0.0f, new_position_offset * 100.0f};
    position = vector_add(position, new_velocity);
}

PhysicsType Kinematic::get_type() const {
    return PhysicsType::KINEMATIC;
}

Vector2D Kinematic::get_acceleration() const {
    return acceleration;
}

float Kinematic::get_mass() const {
    return mass;
}

bool Kinematic::is_affected_by_gravity() const {
    return affected_by_gravity;
}

void Kinematic::set_acceleration(Vector2D new_acceleration) {
    acceleration = new_acceleration;
}

void Kinematic::set_mass(float new_mass) {
    mass = new_mass;
}

void Kinematic::set_affected_by_gravity(bool affected) {
    affected_by_gravity = affected;
}