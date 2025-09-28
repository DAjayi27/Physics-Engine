# Collision Detection

## Collision Types

The engine distinguishes between no collider, circle colliders, and AABB colliders via the `Collision_Type` enum shared across shapes and entities.【F:src/collision/collision_types.h†L8-L14】【F:src/core/entity.h†L22-L26】 Shapes advertise their collider support so the dispatcher can choose the right algorithm.【F:src/shapes/shape.h†L21-L33】

## Dispatch Pipeline

`initialize_collision_system` prepares any global collision data, while `is_colliding` performs shape-aware overlap checks and returns a collision normal when contact occurs.【F:src/collision/collision.h†L8-L23】【F:src/core/world.cpp†L142-L155】 A broad-phase AABB helper is available for fast rejection before expensive shape tests run.【F:src/collision/collision.h†L18-L23】

## Response Handling

When a collision normal is returned, the world defers to `handle_collision`, which applies the appropriate resolution routine for the two entities involved.【F:src/collision/collision.h†L24-L27】【F:src/core/world.cpp†L142-L155】 After resolution, the world records the entity pair so it can detect when collisions end and re-enable gravity or other stateful effects.【F:src/core/world.cpp†L148-L178】
