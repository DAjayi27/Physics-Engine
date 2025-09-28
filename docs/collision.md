# Collision Detection

## Collision Types

The engine distinguishes between no collider, circle colliders, and AABB colliders via the `Collision_Type` enum shared across shapes and entities. Shapes advertise their collider support so the dispatcher can choose the right algorithm.

## Dispatch Pipeline

`initialize_collision_system` prepares any global collision data, while `is_colliding` performs shape-aware overlap checks and returns a collision normal when contact occurs. A broad-phase AABB helper is available for fast rejection before expensive shape tests run.

## Response Handling

When a collision normal is returned, the world defers to `handle_collision`, which applies the appropriate resolution routine for the two entities involved. After resolution, the world records the entity pair so it can detect when collisions end and re-enable gravity or other stateful effects.
