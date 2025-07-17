//
// Created by AJYDAN on 01/07/2025.
//
//
/// \file
/// \brief Implementation of the Particle class for the physics engine.
///
/// This file contains the implementation of the Particle class, which represents
/// a simple physical particle with mass, velocity, and lifetime properties. The
/// class provides methods for manipulating and querying the particle's state.
///
/// \author AJYDAN
/// \date 01/07/2025
///

#include "particle.h"
#include "core/vector.h"

Particle::Particle() {
    // Default constructor - all values are initialized in the header
}

Particle::Particle(float mass, Vector2D velocity, float lifetime, bool is_static) {
    this->mass = mass;
    this->velocity = velocity;
    this->lifetime = lifetime;
    this->static_object = is_static;
}

void Particle::update(float delta_time, float area) {
    if (static_object) {
        return;
    }

    // Decrease lifetime
    lifetime -= delta_time;

    // Apply gravity if enabled
    if (affected_by_gravity) {
        const Vector2D gravity = {0.0f, 981.0f}; // 981 pixels/s²
        velocity = vector_add(velocity, vector_scale(gravity, delta_time));
    }

    // Update position: p = p + v * dt
    position = vector_add(position, vector_scale(velocity, delta_time));
}

PhysicsType Particle::get_type() const {
    return PhysicsType::PARTICLE;
}

float Particle::get_mass() const {
    return mass;
}

bool Particle::is_affected_by_gravity() const {
    return affected_by_gravity;
}

float Particle::get_lifetime() const {
    return lifetime;
}

void Particle::set_mass(float new_mass) {
    mass = new_mass;
}

void Particle::set_affected_by_gravity(bool affected) {
    affected_by_gravity = affected;
}

void Particle::set_lifetime(float new_lifetime) {
    lifetime = new_lifetime;
}

bool Particle::is_alive() const {
    return lifetime > 0.0f;
}