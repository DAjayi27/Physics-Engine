//
// Created by AJYDAN on 02/05/2025.
//

#include "rigid_body.h"

#include <cstdio>

#include "core/vector.h"
#include <math.h>
#include <bits/stl_algo.h>

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
                       bool is_static, bool affected_by_gravity,float ppm) {
    this->mass = mass;
    this->friction = friction;
    this->restitution = restitution;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->static_object = is_static;
    this->affected_by_gravity = affected_by_gravity;
		this->pixelPerMeter = ppm;
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
	// --- Setup constants ---
	const float rho = 1.293f;   // kg/m³ (air) air desity
	const float Cd  = 0.47f;    // sphere-like object
	const float g   = 9.8f;     // gravity m/s²

	// --- Height-dependent wind setup ---
	// Params
	const float H        = 20.0f;     // meters to reach full wind
	const float k        = 10.0f;     // max wind speed increase over H (m/s)
	const float y_ground = 10.0f;    // ground y (meters), y decreases downward

	// Current position (meters)
	Vector2D pos_m = get_position_meters();

	// Height above ground (>= 0 because y increases upward)
	float height = std::max(0.0f, pos_m.y - y_ground);

	// Normalize to [0,1]
	float eta = std::clamp(height / H, 0.0f, 1.0f);

	// Wind speed at this height (negative = leftward, positive = rightward)
	float v_wind_x = -(k * eta);  // zero at/under ground, reaches -k by y >= y_ground + H



	// --- Relative velocities ---
	float vrel_x = velocity.x - v_wind_x;
	float vrel_y = velocity.y; // no wind vertically

	// --- Drag forces (Fd = -0.5 * rho * v * |v| * A * Cd) ---
	float drag_force_x = -0.5f * rho * area * vrel_x * fabsf(vrel_x) * Cd;
	float drag_force_y = -0.5f * rho * area * vrel_y * fabsf(vrel_y) * Cd;

	// --- Gravity force (y only) ---
	float gravitational_force_y = mass * g;

	// --- Net forces ---
	float total_force_x = drag_force_x; // wind already in relative velocity
	float total_force_y = drag_force_y + gravitational_force_y;

	// --- Accelerations ---
	float accel_x = total_force_x / mass;
	float accel_y = total_force_y / mass;

	// --- Update velocity (semi-implicit Euler) ---
	velocity.x += accel_x * delta_time;
	velocity.y += accel_y * delta_time;

	// --- Update position ---
	pos_m.x += velocity.x * delta_time;
	pos_m.y += velocity.y * delta_time;
	printf("%f\n",pos_m.x);
	set_position_meters(pos_m);

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



