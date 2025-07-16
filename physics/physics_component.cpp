
#include "physics_component.h"

Vector2D Physics_Component::get_position() const {
    return position;
}

void Physics_Component::set_position(Vector2D new_position) {
    position = new_position;
}

void Physics_Component::set_position_x(float x) {
    position.x = x;
}

void Physics_Component::set_position_y(float y) {
    position.y = y;
}

Vector2D Physics_Component::get_velocity() const {
    return velocity;
}

void Physics_Component::set_velocity(Vector2D new_velocity) {
    velocity = new_velocity;
}

void Physics_Component::set_velocity_x(float x) {
    velocity.x = x;
}

void Physics_Component::set_velocity_y(float y) {
    velocity.y = y;
}

bool Physics_Component::is_static() const {
    return static_object;
}

void Physics_Component::set_static(bool is_static) {
    static_object = is_static;
}
