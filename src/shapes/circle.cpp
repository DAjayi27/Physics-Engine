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
	Circle::Circle(float radius) : radius(radius) {
	    has_collision = true;
	}

	/**
	 * @brief Sets the radius of the circle.
	 * @param radius The new radius value to set.
	 */
	void Circle::set_radius(float new_radius) {
	    radius = new_radius;
	}

	/**
	 * @brief Gets the radius of the circle.
	 * @return The current radius of the circle.
	 */
	float Circle::get_radius() const {
	    return radius;
	}

	/**
	 * @brief Gets the type of the shape.
	 * @return The shape type, which is CIRCLE for this class.
	 */
	ShapeType Circle::get_type() const {
	    return ShapeType::CIRCLE;
	}

	/**
	 * @brief Calculates the area of the circle.
	 * @details The radius is normalized by dividing by 100 before calculating the area.
	 * @return The area of the circle.
	 */
	float Circle::get_area() const {
	    return std::numbers::pi_v<float> * radius * radius;
	}

	/**
		 * @brief Calculates the area of the circle.
		 * @param PPM the Pixel Per Meter ratio
		 * @details The radius is normalized by dividing by the PixelPerMeter ratio before calculating the area.
		 * @return The area of the circle.
		 */
	float Circle::get_area_normalised(int PPM) const {
			return std::numbers::pi_v<float> * (radius/PPM) * (radius/PPM);
	}

	Collision_Type Circle::get_collision_type() const {
		return CIRCLE_COLLISION;
	}
