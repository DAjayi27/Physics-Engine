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

/**
 * \brief Default constructor for Particle.
 *
 * Initializes all properties to default values:
 * - mass = 0
 * - velocity = {0, 0}
 * - is_static = false
 * - lifetime = 0
 */
Particle::Particle() {
	this->mass = 0;
	this->set_velocity({0,0});
	this->set_is_static(false);
	this->lifetime = 0;
}

/**
 * \brief Constructs a Particle with the specified properties.
 * \param m The mass of the particle.
 * \param v The initial velocity of the particle.
 * \param lifetime The lifetime of the particle.
 * \param isStat Whether the particle is static (immovable).
 */
Particle::Particle(float m, Vector_2D v, float lifetime, bool isStat) {
	this->mass = m;
	this->set_velocity(v);
	this->set_is_static(isStat);
	this->lifetime = lifetime;
}

/**
 * \brief Gets the mass of the particle.
 * \return The mass.
 */
float Particle::get_mass() {
	return mass;
}

/**
 * \brief Checks if the particle is affected by gravity.
 * \return True if affected by gravity, false otherwise.
 */
bool Particle::is_affected_by_gravity() {
	return affected_by_gravity;
}

/**
 * \brief Sets whether the particle is affected by gravity.
 * \param val True to enable gravity, false to disable it.
 */
void Particle::set_affected_by_gravity(bool val) {
	affected_by_gravity = val;
}

/**
 * \brief Sets the mass of the particle.
 * \param m The new mass value.
 */
void Particle::set_mass(float m) {
	mass = m;
}

Physics_Type Particle::get_type() {
	return PHYSICS_PARTICLE;
}