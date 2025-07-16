//
	// Created by AJYDAN on 02/05/2025.
	//

	#include <stdlib.h>
	#include <numbers>
	#include "circle.h"
	#include <math.h>

	/**
	 * @class Circle
	 * @brief Represents a circle shape with a radius and provides methods to calculate its properties.
	 */
	Circle::Circle(float radius) {
	    // Constructor to initialize the circle with a given radius.
	    this->radius = radius;
	}

	/**
	 * @brief Sets the radius of the circle.
	 * @param radius The new radius value to set.
	 */
	void Circle::set_radius(float radius) {
	    this->radius = radius;
	}

	/**
	 * @brief Gets the radius of the circle.
	 * @return The current radius of the circle.
	 */
	float Circle::get_radius() {
	    return this->radius;
	}

	/**
	 * @brief Gets the type of the shape.
	 * @return The shape type, which is CIRCLE for this class.
	 */
	Shape_Type Circle::getType() {
	    return CIRCLE;
	}

	/**
	 * @brief Calculates the area of the circle.
	 * @details The radius is normalized by dividing by 100 before calculating the area.
	 * @return The area of the circle.
	 */
	float Circle::get_area() {
	    float normalised_radius = this->radius / 100;
	    return M_PI * (normalised_radius * normalised_radius);
	}

	Collision_Type Circle::get_collision_type() {
		return CIRCLE_COLLISION;
	}
