# Physics Engine

## Overview
Physics Engine is a C++20 sandbox for experimenting with rigid-body dynamics and simple 2D rendering. The runtime is
built on top of SDL3 and organises simulation state through the `World` class, which steps the physics system, checks
collisions, and draws entities each frame.【F:src/core/world.cpp†L1-L103】 Entities combine a drawable shape, a physics
component, colour data, and a collision type so that game objects can be simulated and rendered consistently.【F:src/core/entity.h†L1-L54】

## Features
- **Real-time world loop** – `World::update` integrates physics and collision resolution before `World::render`
draws the frame using SDL's renderer.【F:src/core/world.cpp†L35-L103】
- **Component-based physics** – Interchangeable components implement rigid bodies, kinematic actors, and particle
behaviour via the `Physics_Component` interface.【F:src/physics/physics_component.h†L1-L53】【F:src/physics/rigid_body.h†L1-L60】
- **Shape primitives** – Circles and axis-aligned rectangles supply area, collision bounds, and render information to
the engine.【F:src/shapes/circle.h†L1-L66】【F:src/shapes/rectangle.h†L1-L60】
- **Collision detection** – The collision system provides AABB checks and resolves contacts between entities during the
update step.【F:src/collision/collision.h†L1-L32】【F:src/core/world.cpp†L71-L143】
- **UI overlay support** – A lightweight UI manager can spawn popup components and handle SDL events alongside the
simulation loop.【F:src/ui/ui_manager.h†L1-L44】【F:src/ui/components/ui_popup.h†L1-L56】

## Project Structure
```
.
├── src/
│   ├── core/           # World orchestration, entities, and vector math
│   ├── physics/        # Physics components (rigid body, kinematic, particle)
│   ├── collision/      # Collision tests and response helpers
│   ├── rendering/      # SDL renderer bindings for entities
│   ├── shapes/         # Circle and rectangle implementations
│   └── ui/             # UI manager and popup components
└── test/               # GoogleTest unit and integration suites
```

## Getting Started
### Prerequisites
- CMake 3.28.3 or newer【F:CMakeLists.txt†L1-L18】
- A C++20-compatible compiler
- SDL3 development libraries available on your system【F:CMakeLists.txt†L19-L82】
- (Optional) GoogleTest is fetched automatically when configuring the project【F:CMakeLists.txt†L8-L18】

### Configure & Build
```bash
cmake -S . -B build
cmake --build build
```
This generates the `Physics_Engine` executable along with dedicated binaries for the component, UI, and combined test
suites.【F:CMakeLists.txt†L20-L117】

### Run the Demo
After building, launch the sandbox application:
```bash
./build/Physics_Engine
```
The demo spawns a falling circle, a static floor rectangle, and processes SDL input through the `World` loop.【F:src/main.cpp†L70-L153】

### Run Tests
GoogleTest targets are registered with CTest. After configuring the project, you can execute the suite with:
```bash
ctest --test-dir build
```
The tests cover vector math, entity behaviour, shape properties, physics updates, collision detection, and world
initialisation.【F:CMakeLists.txt†L84-L139】【F:test/components/vector2d_test.cpp†L1-L53】 Some tests create SDL windows;
ensure your environment supports SDL rendering when running them.

## Key Concepts
- **World** – Manages SDL lifecycle, orchestrates physics updates, collision checks, and UI rendering each frame.【F:src/core/world.cpp†L1-L197】
- **Entity** – Owns a shape, physics component, colour, and collision metadata to represent a simulated object.【F:src/core/entity.h†L1-L54】
- **Physics Components** – Derived from `Physics_Component`, these classes update positions and velocities based on
delta time, mass, gravity, and custom rules.【F:src/physics/physics_component.h†L1-L53】【F:src/physics/rigid_body.cpp†L1-L130】
- **Renderer** – Utility namespace that initialises SDL render state and draws entities by sampling their geometry and
colour.【F:src/rendering/renderer.h†L1-L28】
- **UI Manager** – Bridges SDL events to in-engine UI components such as popup overlays, enabling runtime controls and
diagnostics.【F:src/ui/ui_manager.h†L1-L44】【F:src/ui/components/ui_popup.cpp†L1-L96】

## Extending the Engine
1. **Add a new shape** by deriving from `Shape` and implementing area and rendering helpers, then register any new
collision logic in `collision.cpp`.
2. **Create a physics behaviour** by subclassing `Physics_Component` and overriding `update` to apply custom forces.
3. **Introduce UI panels** by extending `UiComponent` and enqueueing new actions through `UiManager`.
4. **Spawn new entities** in `main.cpp` or your own entry point by composing shapes, physics components, and colours
to suit your simulation.

## Troubleshooting
- SDL initialisation issues usually stem from missing runtime libraries. Confirm that `SDL3::SDL3` is discoverable by
CMake and that the SDL dynamic libraries are on your system path.【F:CMakeLists.txt†L19-L82】
- If tests fail to create windows, ensure a display server is available or run the suite in an environment with SDL
headless support enabled.【F:CMakeLists.txt†L84-L139】
