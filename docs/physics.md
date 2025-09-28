# Physics Components

## Shared Interface

All physics behaviors derive from `Physics_Component`, which standardizes position, velocity, static state management, and an `update(delta_time, area)` hook invoked each frame. The base class also tracks conversions between pixel and meter units so components can interpret geometry consistently.

## Rigid Bodies

`Rigid_Body` models mass-based dynamics with configurable acceleration, friction, restitution, and gravity toggles. It exposes helpers for applying forces or impulses, making it suitable for most interactive objects that need realistic momentum.

## Particles

`Particle` trades complexity for lightweight updates, adding lifetime tracking for short-lived effects while still supporting gravity and configurable mass. Use this component for visual bursts or debris where deterministic motion is less critical.

## Kinematic Controllers

`Kinematic` components serve scripted or player-controlled actors. They maintain acceleration and optional gravity influence while leaving final velocities under caller control. Because they implement the same interface, kinematic entities plug into the world loop without additional branching.
