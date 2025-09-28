# Testing

## Component Suites

Low-level math and physics behavior is validated under `test/components`. Vector helpers cover arithmetic, magnitudes, distances, and normalization to ensure deterministic physics inputs. The shared physics interface and rigid body implementation are checked for correct default state, getters/setters, and impulse handling so motion stays predictable. Collision helpers verify both broad-phase AABB rejection and overlap normals for circle entities.

## Integration Coverage

`test/ui/world_test.cpp` exercises world lifecycle behaviors, confirming entity counting, batch insertion, and SDL-backed initialization/teardown routines. These integration checks ensure the main loop wiring remains stable when refactoring core systems.

## Extending Tests

When adding new modules, place unit tests alongside similar coverage under `test/components` or `test/ui`, update `CMakeLists.txt` if new binaries are needed, and rely on `ctest` discovery to pick up the additional targets automatically.
