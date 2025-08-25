//
// Created by AJYDAN on 02/05/2025.
//

#pragma once

#include <SDL3/SDL_pixels.h>
#include <memory>
#include "src/physics/physics_component.h"
#include "src/shapes/shape.h"

/**
 * @brief Represents an entity in the physics simulation
 * 
 * An entity combines a shape, physics component, visual properties,
 * and collision type into a single game object.
 */
class Entity {
private:

public:
	uint64_t entity_id;
  std::unique_ptr<Shape> shape;
  std::unique_ptr<Physics_Component> physics;
  SDL_Color color;
  Collision_Type collision_type;

  // Constructors
  Entity();
  // Entity(std::unique_ptr<Shape> shape,
  //        std::unique_ptr<Physics_Component> physics,
  //        SDL_Color color);
	Entity(unsigned int entity_id, std::unique_ptr<Shape> shape,
			 std::unique_ptr<Physics_Component> physics,
			 SDL_Color color);

  // Position methods
  Vector2D get_position() const;
  void set_position(Vector2D position);
  void set_position_x(float x);
  void set_position_y(float y);

  // Velocity methods
  Vector2D get_velocity() const;
  void set_velocity(Vector2D velocity);
  void set_velocity_x(float x);
  void set_velocity_y(float y);

  // Physics state methods
  bool is_static() const;
  void set_static(bool is_static);
};

// Entity factory functions
Entity create_circle_entity(float x, float y, float radius, SDL_Color color, 
                           PhysicsType physics_type, float mass);
Entity create_rectangle_entity(float x, float y, float width, float height, 
                              bool is_static, SDL_Color color);

// Legacy compatibility
#define create_circle_zero_entity create_circle_entity
#define create_rect_physics_entity create_rectangle_entity
