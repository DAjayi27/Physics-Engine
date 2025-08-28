//
// Created by AJYDAN on 02/05/2025.
//

#include "rigid_body.h"

#include <cstdio>

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
    }

    // // Apply friction
    // if (friction > 0.0f) {
    //     Vector2D friction_force = vector_scale(velocity, -friction);
    //     velocity = vector_add(velocity, vector_scale(friction_force, delta_time));
    // }
}

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
 * Fd – Drag force;
 *	ρ – Airs's density;
 *	u – Relative velocity;
 *	A – Reference area; and
 *	Cd – Drag coefficient.
 *
 ***/
void Rigid_Body::update_gravity_physics(float delta_time, float area) {
  if (static_object || !affected_by_gravity) {
      return;
  }

	// extra force in X (e.g., wind pushing right)
	float wind_force_x = 1000.0f;

	// Air density (ρ) and drag coefficient (Cd)
	const float rho = 1.293f;   // kg/m³ (air)
	const float Cd = 0.47f;     // sphere-like object

	// --- Drag force (applies in both axes) ---
	float drag_force_x = -0.5f * rho * area * velocity.x * fabsf(velocity.x) * Cd;
	float drag_force_y = -0.5f * rho * area * velocity.y * fabsf(velocity.y) * Cd;

	// --- Gravity (y-axis only) ---
	float gravitational_force_y = mass * 98.0f;

	// --- Net forces ---
	float total_force_x = drag_force_x +wind_force_x;
	float total_force_y = drag_force_y + gravitational_force_y;

	// --- Accelerations ---
	float accel_x = total_force_x / mass;
	float accel_y = total_force_y / mass;

	// --- Position updates ---
	float new_position_offset_x = velocity.x * delta_time + 0.5f * accel_x * delta_time * delta_time;
	float new_position_offset_y = velocity.y * delta_time + 0.5f * accel_y * delta_time * delta_time;

	// --- Velocity updates ---
	velocity.x += accel_x * delta_time;
	velocity.y += accel_y * delta_time;

	// --- Update position ---
	position.x += new_position_offset_x;
	position.y += new_position_offset_y;
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



