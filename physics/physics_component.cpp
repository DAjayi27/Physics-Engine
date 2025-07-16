
#include "physics_component.h"

#include <string.h>


/**
 * @brief Gets the velocity of the physics component.
 * @return A reference to the velocity vector.
 */
Vector_2D Physics_Component::get_velocity() {
	return velocity;
}

/**
 * @brief Sets the velocity of the physics component.
 * @param v The new velocity vector.
 */
void Physics_Component::set_velocity(Vector_2D v) {
	velocity = v;
}


void Physics_Component::set_velocity_y( float y) {
	velocity.y = y;
}

void Physics_Component::set_velocity_x( float x) {
	velocity.x = x;
}


/**
 * @brief Gets the position of the physics component.
 * @return A reference to the position vector.
 */
Vector_2D Physics_Component::get_position() {
	return position;
}


void Physics_Component:: set_position_y( float y) {
	position.y = y;
}

void Physics_Component::set_position_x( float x) {
	position.x = x;
}

/**
 * @brief Sets the position of the physics component.
 * @param position The new position vector.
 */
void Physics_Component::set_position(Vector_2D position) {
	this->position = position;
}

/**
 * @brief Sets whether the rigid body is static.
 * @param val True to make the rigid body static, false otherwise.
 */
void Physics_Component::set_is_static(bool val) {
	is_static = val;
}

/**
 * @brief Checks if the rigid body is static.
 * @return True if the rigid body is static, false otherwise.
 */
bool Physics_Component::get_is_static() {
	return is_static;
}
