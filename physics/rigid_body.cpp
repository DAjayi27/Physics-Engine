//
// Created by AJYDAN on 02/05/2025.
//

#include "rigid_body.h"

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
	this->mass = 0;
	this->friction = 0;
	this->restitution = 0;
	this->set_velocity({0,0});
	this->acceleration = {0,0};
	this->set_is_static(false);
	this->affected_by_gravity = true;
}

/**
 * @brief Constructs a Rigid_Body with the specified properties.
 * @param m The mass of the rigid body.
 * @param f The friction coefficient of the rigid body.
 * @param r The restitution (bounciness) of the rigid body.
 * @param v The initial velocity of the rigid body.
 * @param a The initial acceleration of the rigid body.
 * @param isStat Whether the rigid body is static (immovable).
 * @param affectedGravity Whether the rigid body is affected by gravity.
 */
Rigid_Body::Rigid_Body(float m, float f, float r, Vector_2D v, Vector_2D a, bool isStat, bool affectedGravity) {
    this->mass = m;
    this->friction = f;
    this->restitution = r;
    this->set_velocity(v);
    this->acceleration = a;
    this->set_is_static(isStat);
    this->affected_by_gravity = affectedGravity;
}



/**
 * @brief Gets the friction coefficient of the rigid body.
 * @return The friction coefficient.
 */
float Rigid_Body::get_friction() {
    return friction;
}

/**
 * @brief Gets the mass of the rigid body.
 * @return The mass.
 */
float Rigid_Body::get_mass() {
    return mass;
}

/**
 * @brief Gets the restitution (bounciness) of the rigid body.
 * @return The restitution value.
 */
float Rigid_Body::get_restitution() {
    return restitution;
}


/**
 * @brief Checks if the rigid body is affected by gravity.
 * @return True if affected by gravity, false otherwise.
 */
bool Rigid_Body::is_affected_by_gravity() {
    return affected_by_gravity;
}

/**
 * @brief Gets the acceleration of the rigid body.
 * @return A reference to the acceleration vector.
 */
const Vector_2D Rigid_Body::get_acceleration() {
    return acceleration;
}

/**
 * @brief Sets whether the rigid body is affected by gravity.
 * @param val True to enable gravity, false to disable it.
 */
void Rigid_Body::set_affected_by_gravity(bool val) {
    affected_by_gravity = val;
}

/**
 * @brief Sets the friction coefficient of the rigid body.
 * @param f The new friction coefficient.
 */
void Rigid_Body::set_friction(float f) {
    friction = f;
}

/**
 * @brief Sets the mass of the rigid body.
 * @param m The new mass value.
 */
void Rigid_Body::set_mass(float m) {
    mass = m;
}

/**
 * @brief Sets the restitution (bounciness) of the rigid body.
 * @param r The new restitution value.
 */
void Rigid_Body::set_restitution(float r) {
    restitution = r;
}

/**
 * @brief Sets the acceleration of the rigid body.
 * @param a The new acceleration vector.
 */
void Rigid_Body::set_acceleration(Vector_2D a) {
	acceleration = a;
}

Physics_Type Rigid_Body::get_type() {
	return PHYSICS_RIGID_BODY;
}



