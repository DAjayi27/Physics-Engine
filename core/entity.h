//
// Created by AJYDAN on 02/05/2025.
//

#pragma once

#include <SDL3/SDL_pixels.h>
#include <memory>
#include "physics/physics_component.h"
#include "shapes/shape.h"

/**
 * @brief Represents an entity with shape, physics, position, and color.
 */
class Entity {




public:

	std::unique_ptr<Shape> shape;
	std::unique_ptr<Physics_Component> physics;
	SDL_Color color;
	Collision_Type collision;

  // Constructors
  Entity();
  Entity(std::unique_ptr<Shape> shape,  std::unique_ptr<Physics_Component> physics,SDL_Color color);
	void set_position(Vector_2D position);
	void set_position_x(float position);
	void set_position_y(float position);

	Vector_2D get_position();


};
