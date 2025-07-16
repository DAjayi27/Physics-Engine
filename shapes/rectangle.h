//
// Created by AJYDAN on 01/05/2025.
//

#pragma once
#include "shape.h"

class Rectangle : public Shape{

  float width;
  float height;

  public:
		Rectangle(float width,float height);
		Rectangle(float width,float height,bool has_collision);
		void set_width(float width);
		void set_height(float height);
		float get_width();
		float get_height();
	  Shape_Type getType() override;
		Collision_Type get_collision_type() override;
		float get_area() override;

};






