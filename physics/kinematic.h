#pragma once

#include "physics_component.h"

/**
 * @brief Kinematic physics component for controlled movement
 * 
 * Implements physics behavior for objects with controlled movement,
 * typically used for player characters or scripted objects.
 */
class Kinematic : public Physics_Component {
private:
    bool affected_by_gravity = true;
    Vector2D acceleration{0.0f, 0.0f};
    float mass = 1.0f;
		void update_gravity_physics(float delta_time, float area);

public:
    // Constructors
    Kinematic();
    Kinematic(float mass, Vector2D velocity, Vector2D acceleration, 
              bool is_static, bool affected_by_gravity);

    // Core physics methods
    void update(float delta_time, float area) override;
    PhysicsType get_type() const override;

    // Property getters
    Vector2D get_acceleration() const;
    float get_mass() const;
    bool is_affected_by_gravity() const;

    // Property setters
    void set_acceleration(Vector2D acceleration);
    void set_mass(float mass);
    void set_affected_by_gravity(bool affected);
};
