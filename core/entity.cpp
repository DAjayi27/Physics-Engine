// core/entity.cpp

#include "entity.h"

#include "shapes/circle.h"
#include "shapes/rectangle.h"

// Default constructor
Entity::Entity() : shape(nullptr), physics(nullptr), color{0, 0, 0, 255},collision(NONE) {}

Entity::Entity(std::unique_ptr<Shape> shape, std::unique_ptr<Physics_Component> physics,SDL_Color color) {

	this->shape = std::move(shape);
	this->physics = std::move(physics);
	this->color = color;
}

Vector_2D Entity::get_position() {
	return this->physics->get_position();
}

void Entity::set_position(Vector_2D position) {

	this->physics->set_position(position);

}

void Entity::set_position_x(float position) {
	this->physics->set_position_x(position);
}



void Entity::set_position_y(float position) {
	this->physics->set_position_y(position);
}



