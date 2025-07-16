//
// Created by AJYDAN on 02/05/2025.
//

#pragma once
#include "collision/collision_types.h"

typedef enum shape_type{
    NO_SHAPE,
    CIRCLE,
    RECTANGLE,
    POLYGON,
    TRIANGLE
}Shape_Type;

class Shape {

	public:
		virtual Shape_Type getType()  = 0;
		virtual Collision_Type get_collision_type()  = 0;
		virtual float get_area() = 0;
		virtual  ~Shape() = default;

	protected:
		bool has_collider = false;

};


