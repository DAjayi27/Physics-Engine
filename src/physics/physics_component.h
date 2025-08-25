//
// Created by AJYDAN on 02/05/2025.
//

#pragma once

#include "src/core/vector.h"

/**
 * @brief Enumeration of physics component types
 */
enum class PhysicsType {
    NONE,
    RIGID_BODY,
    KINEMATIC,
    PARTICLE
};

// Legacy compatibility
using Physics_Type = PhysicsType;

/**
 * @brief Abstract base class for physics components
 * 
 * Provides common interface for different types of physics behavior
 * including position, velocity, and static state management.
 */
class Physics_Component {
public:
  virtual ~Physics_Component() = default;

  // Core physics update
  virtual void update(float delta_time, float areaa) = 0;
  virtual PhysicsType get_type() const = 0;

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

  // Static state methods
  bool is_static() const;
  void set_static(bool is_static);



protected:
  Vector2D position{0.0f, 0.0f};
  Vector2D velocity{0.0f, 0.0f};
  bool static_object = false;
};

// extern Physics_Component create_physics_component(Physics_Type type, Vector_2D velocity , Vector_2D acceleration , float mass);

