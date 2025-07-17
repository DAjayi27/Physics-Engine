#pragma once

#include "physics_component.h"

/**
 * @brief Particle physics component for simple particle effects
 * 
 * Implements lightweight physics behavior for particles with lifetime
 * and simplified physics calculations.
 */
class Particle : public Physics_Component {
private:
    float lifetime = 1.0f;
    float mass = 1.0f;
    bool affected_by_gravity = true;

public:
    // Constructors
    Particle();
    Particle(float mass, Vector2D velocity, float lifetime, bool is_static);

    // Core physics methods
    void update(float delta_time, float area) override;
    PhysicsType get_type() const override;

    // Property getters
    float get_mass() const;
    bool is_affected_by_gravity() const;
    float get_lifetime() const;

    // Property setters
    void set_mass(float mass);
    void set_affected_by_gravity(bool affected);
    void set_lifetime(float lifetime);

    // Particle-specific methods
    bool is_alive() const;
};
