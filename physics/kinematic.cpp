//
// Created by AJYDAN on 01/07/2025.
//

#include "kinematic.h"


Kinematic::Kinematic() {
	this->acceleration = {0,0};
	this->mass  = 0;
	this->affected_by_gravity = false;
}

Kinematic::Kinematic(float mass, Vector_2D velocity, Vector_2D a, bool isStat, bool affectedGravity) {
	this->mass = mass;
	this->set_velocity(velocity);
	this->acceleration = a;
	this->set_is_static(isStat);
	this->affected_by_gravity = affectedGravity;
}




/**
 * @brief Checks if the rigid body is affected by gravity.
 * @return True if affected by gravity, false otherwise.
 */
bool Kinematic::is_affected_by_gravity() {
	return affected_by_gravity;
}

/**
 * @brief Gets the acceleration of the rigid body.
 * @return A reference to the acceleration vector.
 */
const Vector_2D Kinematic::get_acceleration() {
	return acceleration;
}

/**
 * @brief Gets the mass of the rigid body.
 * @return The mass.
 */
float Kinematic::get_mass() {
	return mass;
}

/**
 * @brief Sets the acceleration of the rigid body.
 * @param a The new acceleration vector.
 */
void Kinematic::set_acceleration(Vector_2D a) {


	acceleration = a;
}


/**
 * @brief Sets whether the rigid body is affected by gravity.
 * @param val True to enable gravity, false to disable it.
 */
void Kinematic::set_affected_by_gravity(bool val) {
	affected_by_gravity = val;
}

/**
 * @brief Sets the mass of the rigid body.
 * @param m The new mass value.
 */
void Kinematic::set_mass(float m) {
	mass = m;
}

Physics_Type Kinematic::get_type() {
	return PHYSICS_KINEMATIC;
}