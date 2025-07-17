//
// Created by AJYDAN on 02/05/2025.
//

#include "rigid_body.h"
#include "core/vector.h"
#include <math.h>

/**
 * @class Rigid_Body
 * @brief Represents a rigid body in a physics simulation, with properties such as mass, velocity, acceleration, and more.
 */

/**
 * @brief Default constructor for Rigid_Body.
 *
 * Initializes all properties to default values:
 * - mass = 0
 * - friction = 0
 * - restitution = 0
 * - velocity = {0, 0}
 * - acceleration = {0, 0}
 * - is_static = false
 * - affected_by_gravity = true
 */

Rigid_Body::Rigid_Body() {
    // Default constructor - all values are initialized in the header
}

Rigid_Body::Rigid_Body(float mass, float friction, float restitution, 
                       Vector2D velocity, Vector2D acceleration, 
                       bool is_static, bool affected_by_gravity) {
    this->mass = mass;
    this->friction = friction;
    this->restitution = restitution;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->static_object = is_static;
    this->affected_by_gravity = affected_by_gravity;
}

void Rigid_Body::update(float delta_time,float area) {
    if (static_object) {
        return;
    }

    // Apply gravity physics with drag forces if enabled
    if (affected_by_gravity) {
        update_gravity_physics(delta_time, area);
    } else {
        // Apply basic gravity without drag
        const Vector2D gravity = {0.0f, 981.0f}; // 981 pixels/s²
        acceleration = vector_add(acceleration, gravity);
        
        // Update velocity: v = v + a * dt
        velocity = vector_add(velocity, vector_scale(acceleration, delta_time));
        
        // Update position: p = p + v * dt
        position = vector_add(position, vector_scale(velocity, delta_time));
        
        // Reset acceleration for next frame
        acceleration = {0.0f, 0.0f};
    }

    // Apply friction
    if (friction > 0.0f) {
        Vector2D friction_force = vector_scale(velocity, -friction);
        velocity = vector_add(velocity, vector_scale(friction_force, delta_time));
    }
}

// Private method for gravity physics calculations
void Rigid_Body::update_gravity_physics(float delta_time, float area) {
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

PhysicsType Rigid_Body::get_type() const {
    return PhysicsType::RIGID_BODY;
}

Vector2D Rigid_Body::get_acceleration() const {
    return acceleration;
}

float Rigid_Body::get_mass() const {
    return mass;
}

float Rigid_Body::get_restitution() const {
    return restitution;
}

bool Rigid_Body::is_affected_by_gravity() const {
    return affected_by_gravity;
}

float Rigid_Body::get_friction() const {
    return friction;
}

void Rigid_Body::set_acceleration(Vector2D new_acceleration) {
    acceleration = new_acceleration;
}

void Rigid_Body::set_mass(float new_mass) {
    mass = new_mass;
}

void Rigid_Body::set_restitution(float new_restitution) {
    restitution = new_restitution;
}

void Rigid_Body::set_affected_by_gravity(bool affected) {
    affected_by_gravity = affected;
}

void Rigid_Body::set_friction(float new_friction) {
    friction = new_friction;
}

void Rigid_Body::apply_force(Vector2D force) {
    if (mass > 0.0f) {
        Vector2D force_acceleration = vector_scale(force, 1.0f / mass);
        acceleration = vector_add(acceleration, force_acceleration);
    }
}

void Rigid_Body::apply_impulse(Vector2D impulse) {
    if (mass > 0.0f) {
        Vector2D velocity_change = vector_scale(impulse, 1.0f / mass);
        velocity = vector_add(velocity, velocity_change);
    }
}



