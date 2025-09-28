# Physics Components

## Shared Interface

All physics behaviors derive from `Physics_Component`, which standardizes position, velocity, static state management, and an `update(delta_time, area)` hook invoked each frame.【F:src/physics/physics_component.h†L22-L63】【F:src/core/world.cpp†L119-L132】 The base class also tracks conversions between pixel and meter units so components can interpret geometry consistently.【F:src/physics/physics_component.h†L37-L63】

## Rigid Bodies

`Rigid_Body` models mass-based dynamics with configurable acceleration, friction, restitution, and gravity toggles.【F:src/physics/rigid_body.h†L15-L55】 It exposes helpers for applying forces or impulses, making it suitable for most interactive objects that need realistic momentum.

## Particles

`Particle` trades complexity for lightweight updates, adding lifetime tracking for short-lived effects while still supporting gravity and configurable mass.【F:src/physics/particle.h†L11-L38】 Use this component for visual bursts or debris where deterministic motion is less critical.

## Kinematic Controllers

`Kinematic` components serve scripted or player-controlled actors. They maintain acceleration and optional gravity influence while leaving final velocities under caller control.【F:src/physics/kinematic.h†L11-L37】 Because they implement the same interface, kinematic entities plug into the world loop without additional branching.
