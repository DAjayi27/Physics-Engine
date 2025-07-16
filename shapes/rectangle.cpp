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
	Rectangle::Rectangle(float width, float height) {
	    // Constructor to initialize a rectangle with width and height, without collision.
	    this->has_collider = false;
	    this->width = width;
	    this->height = height;
	}

	/**
	 * @brief Constructor to initialize a rectangle with width, height, and collision properties.
	 * @param width The width of the rectangle.
	 * @param height The height of the rectangle.
	 * @param has_collision Whether the rectangle has collision enabled.
	 */
	Rectangle::Rectangle(float width, float height, bool has_collision) {
	    if (!has_collision) {
	        this->has_collider = false;
	    } else {
	        this->has_collider = true;
	    }
	    this->width = width;
	    this->height = height;
	}

	/**
	 * @brief Gets the height of the rectangle.
	 * @return The height of the rectangle.
	 */
	float Rectangle::get_height() {
	    return this->height;
	}

	/**
	 * @brief Gets the width of the rectangle.
	 * @return The width of the rectangle.
	 */
	float Rectangle::get_width() {
	    return this->width;
	}

	/**
	 * @brief Sets the height of the rectangle.
	 * @param height The new height value to set.
	 */
	void Rectangle::set_height(float height) {
	    this->height = height;
	}

	/**
	 * @brief Sets the width of the rectangle.
	 * @param width The new width value to set.
	 */
	void Rectangle::set_width(float width) {
	    this->width = width;
	}

	/**
	 * @brief Gets the type of the shape.
	 * @return The shape type, which is RECTANGLE for this class.
	 */
	Shape_Type Rectangle::getType() {
	    return RECTANGLE;
	}

	/**
	 * @brief Calculates the area of the rectangle.
	 * @return The area of the rectangle (width * height).
	 */
	float Rectangle::get_area() {
	    return this->height * this->width;
	}

	Collision_Type Rectangle::get_collision_type() {
		return AABB_COLLISION;
	}
