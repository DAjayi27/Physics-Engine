# Core Systems

## Entities

Entities bundle a renderable shape, a physics component, draw color, and collision metadata, all identified by a unique `entity_id`.【F:src/core/entity.h†L22-L58】 Factory helpers exist for quickly creating circle or rectangle entities with preconfigured physics traits.【F:src/core/entity.h†L54-L58】 Position and velocity accessors simply forward to the underlying physics component so motion logic stays encapsulated.【F:src/core/entity.h†L37-L51】

## World Orchestration

`World` owns the collection of active entities and is responsible for the simulation loop. It counts entities, supports batched insertion, and exposes `update`, `render`, and UI handling entry points.【F:src/core/world.h†L27-L60】【F:src/core/world.cpp†L42-L206】 Initialization sequences set up the renderer, collision system, SDL window, and UI manager before gameplay begins.【F:src/core/world.cpp†L22-L112】【F:src/core/world.cpp†L186-L206】 During each frame, the world tracks elapsed time, clears stale collision pairs, runs broad collision checks, and invokes each physics component's update with shape area information.【F:src/core/world.cpp†L54-L132】【F:src/core/world.cpp†L142-L160】

## Math Utilities

`Vector2D` is a lightweight struct supplying component access and a suite of helper functions for arithmetic, magnitudes, distances, and dot products.【F:src/core/vector.h†L8-L27】 These utilities are used throughout the physics and collision systems for deterministic calculations.
