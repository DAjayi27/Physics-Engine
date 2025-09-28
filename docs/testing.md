# Testing

## Component Suites

Low-level math and physics behavior is validated under `test/components`. Vector helpers cover arithmetic, magnitudes, distances, and normalization to ensure deterministic physics inputs.【F:test/components/vector2d_test.cpp†L1-L68】 The shared physics interface and rigid body implementation are checked for correct default state, getters/setters, and impulse handling so motion stays predictable.【F:test/components/physics_component_test.cpp†L1-L31】【F:test/components/rigid_body_test.cpp†L1-L32】 Collision helpers verify both broad-phase AABB rejection and overlap normals for circle entities.【F:test/components/collision_test.cpp†L1-L28】

## Integration Coverage

`test/ui/world_test.cpp` exercises world lifecycle behaviors, confirming entity counting, batch insertion, and SDL-backed initialization/teardown routines.【F:test/ui/world_test.cpp†L1-L38】 These integration checks ensure the main loop wiring remains stable when refactoring core systems.

## Extending Tests

When adding new modules, place unit tests alongside similar coverage under `test/components` or `test/ui`, update `CMakeLists.txt` if new binaries are needed, and rely on `ctest` discovery to pick up the additional targets automatically.【F:CMakeLists.txt†L102-L120】
