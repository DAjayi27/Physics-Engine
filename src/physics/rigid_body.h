//
// Created by AJYDAN on 02/05/2025.
//

#pragma once

#include "physics_component.h"

/**
 * @brief Rigid body physics component with mass, friction, and gravity support
 * 
 * Implements realistic physics behavior including acceleration, mass-based movement,
 * friction, restitution (bounciness), and gravity effects.
 */
class Rigid_Body : public Physics_Component {
private:
    Vector2D acceleration{0.0f, 0.0f};
    float mass = 1.0f;
    float restitution = 0.5f;
    bool affected_by_gravity = true;
    float friction = 0.1f;


    // Private gravity physics method
    void update_gravity_physics(float delta_time, float area);

public:
    // Constructors
    Rigid_Body();
    Rigid_Body(float mass, float friction, float restitution, 
               Vector2D velocity, Vector2D acceleration, 
               bool is_static, bool affected_by_gravity);

    // Core physics methods
    void update(float delta_time,float area) override;
    PhysicsType get_type() const override;

    // Property getters
    Vector2D get_acceleration() const;
    float get_mass() const;
    float get_restitution() const;
    bool is_affected_by_gravity() const;
    float get_friction() const;

    // Property setters
    void set_acceleration(Vector2D acceleration);
    void set_mass(float mass);
    void set_restitution(float restitution);
    void set_affected_by_gravity(bool affected);
    void set_friction(float friction);

    // Physics calculations
    void apply_force(Vector2D force);
    void apply_impulse(Vector2D impulse);
};
