//
	// Created by AJYDAN on 01/05/2025.
	//

	#include "rectangle.h"

	#include <stdlib.h>

#include "circle.h"

/**
	 * @class Rectangle
	 * @brief Represents a rectangle shape with width, height, and optional collision properties.
	 */
	Rectangle::Rectangle(float width, float height) 
    : width(width), height(height) {
    has_collision = false;
}

Rectangle::Rectangle(float width, float height, bool has_collision) 
    : width(width), height(height) {
    this->has_collision = has_collision;
}

ShapeType Rectangle::get_type() const {
    return ShapeType::RECTANGLE;
}

Collision_Type Rectangle::get_collision_type() const {
    return AABB_COLLISION;
}

float Rectangle::get_area() const {
    return width * height;
}

float Rectangle::get_width() const {
    return width;
}

float Rectangle::get_height() const {
    return height;
}

void Rectangle::set_width(float new_width) {
    width = new_width;
}

void Rectangle::set_height(float new_height) {
    height = new_height;
}
