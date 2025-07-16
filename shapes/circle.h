//
// Created by AJYDAN on 02/05/2025.
//

#pragma once
#include "shape.h"


class Circle : public Shape{

	float radius;

	public:
		explicit Circle(float radius);
		float get_radius();
		void set_radius(float radius);
		Shape_Type getType() override;
		Collision_Type get_collision_type() override;
		float get_area() override;
};
