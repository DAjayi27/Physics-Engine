# Core Systems

## Entities

Entities bundle a renderable shape, a physics component, draw color, and collision metadata, all identified by a unique `entity_id`. Factory helpers exist for quickly creating circle or rectangle entities with preconfigured physics traits. Position and velocity accessors simply forward to the underlying physics component so motion logic stays encapsulated.

## World Orchestration

`World` owns the collection of active entities and is responsible for the simulation loop. It counts entities, supports batched insertion, and exposes `update`, `render`, and UI handling entry points. Initialization sequences set up the renderer, collision system, SDL window, and UI manager before gameplay begins. During each frame, the world tracks elapsed time, clears stale collision pairs, runs broad collision checks, and invokes each physics component's update with shape area information.

## Math Utilities

`Vector2D` is a lightweight struct supplying component access and a suite of helper functions for arithmetic, magnitudes, distances, and dot products. These utilities are used throughout the physics and collision systems for deterministic calculations.
