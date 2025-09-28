# Physics Engine

A modular 2D physics sandbox written in modern C++ and rendered with SDL3. The
engine bundles rigid body dynamics, collision detection, and a lightweight UI
layer into a single component-based architecture that is easy to extend for
experiments or teaching demos.

## Features

- **Entity-component design** – Every `Entity` owns a renderable `Shape` and a
  `Physics_Component`, letting you mix rigid bodies, particles, or kinematic
  actors in the same world. 【F:src/core/entity.h†L16-L54】
- **Deterministic physics integration** – `Rigid_Body`, `Particle`, and
  `Kinematic` components expose friction, restitution, and gravity controls so
  that simulations remain stable across frame rates. 【F:src/physics/rigid_body.h†L11-L47】【F:src/physics/particle.h†L10-L58】
- **Collision system with resolution** – Circle and rectangle shapes can be
  checked with broad-phase AABB tests before dispatching to collision
  resolution routines. 【F:src/collision/collision.h†L6-L29】【F:src/shapes/circle.h†L8-L34】【F:src/shapes/rectangle.h†L8-L36】
- **SDL3 rendering pipeline** – `Renderer::render_entity` draws world entities
  and UI overlays using SDL textures and primitive drawing. 【F:src/rendering/renderer.h†L7-L36】
- **UI actions and overlays** – The `UiManager` manages popup components and
  queues UI actions triggered during the simulation loop. 【F:src/ui/ui_manager.h†L19-L44】【F:src/ui/components/ui_popup.h†L9-L51】
- **Extensive automated tests** – Component and UI integration tests cover
  vector math, physics updates, collision handling, and world orchestration via
  GoogleTest. 【F:test/components/vector2d_test.cpp†L1-L49】【F:test/components/collision_test.cpp†L1-L83】【F:test/ui/world_test.cpp†L1-L98】

## Repository Layout

| Path | Description |
| --- | --- |
| `src/core/` | World orchestration, entity management, and math primitives. |
| `src/physics/` | Physics component hierarchy and integrators. |
| `src/collision/` | Collision detection and response helpers. |
| `src/shapes/` | Renderable geometry primitives shared by physics and rendering. |
| `src/rendering/` | SDL-backed renderer that draws entities and UI widgets. |
| `src/ui/` | Immediate-mode style UI components, actions, and manager logic. |
| `test/components/` | Pure unit tests for math, physics, and collision code. |
| `test/ui/` | SDL-backed integration tests that exercise the world loop. |

## Build Requirements

- A compiler with **C++20** support.
- **CMake 3.28** or newer. 【F:CMakeLists.txt†L1-L6】
- **SDL3 development libraries** discoverable via `find_package(SDL3 REQUIRED)`. 【F:CMakeLists.txt†L18-L19】
- (Optional) `SDL3_image` if you enable the commented texture loading hooks.

GoogleTest is fetched automatically through `FetchContent`, so no system-wide
installation is required. 【F:CMakeLists.txt†L8-L17】

## Building the Project

```bash
cmake -S . -B build
cmake --build build
```

The default target compiles the `Physics_Engine` executable along with two test
runners:

- `Physics_Engine_Component_Tests` for headless unit tests.
- `Physics_Engine_UI_Tests` for SDL-driven integration checks.

All targets link against SDL3 and are generated in the chosen build directory. 【F:CMakeLists.txt†L21-L114】

## Running the Simulation

1. Build the project.
2. Ensure SDL3 can create a window on your platform (e.g., X11, Wayland,
   or Windows/macOS desktop session).
3. Launch the executable:

   ```bash
   ./build/Physics_Engine
   ```

The main loop (`World::update`) handles SDL events, processes UI actions, runs
physics, and renders entities each frame. 【F:src/core/world.h†L24-L59】 Use the
arrow keys to nudge the selected entity around (`handle_input` in `main.cpp`). 【F:src/main.cpp†L41-L55】

## Running Tests

After building, execute the GoogleTest suites from the build directory:

```bash
cd build
ctest --output-on-failure
```

Individual binaries can be run directly if you want to focus on a single suite:

```bash
./Physics_Engine_Component_Tests
./Physics_Engine_UI_Tests
```

Both test executables are registered with `gtest_discover_tests`, so `ctest`
will automatically enumerate the GoogleTest cases. 【F:CMakeLists.txt†L116-L120】

## Extending the Engine

- **Add a new shape** by subclassing `Shape`, implementing `get_type`,
  `get_bounds`, and `render`, then composing it into an `Entity`. 【F:src/shapes/shape.h†L8-L44】
- **Create a custom physics component** by deriving from
  `Physics_Component`, overriding `update`, and exposing configuration knobs
  similar to `Rigid_Body`. 【F:src/physics/physics_component.h†L9-L59】【F:src/physics/rigid_body.h†L26-L47】
- **Hook UI controls** by creating a `UiComponent` and pushing `UIAction`
  instances onto the manager queue. 【F:src/ui/components/ui_component.h†L8-L43】【F:src/ui/ui_action.h†L8-L55】

Because the world stores entities as `std::unique_ptr`, ownership stays clear
and components can share data through simple pointers or events.

## Detailed Documentation

Additional module-by-module guides live in [`docs/`](docs/README.md), covering
architecture, core systems, physics, collision detection, shapes, rendering,
UI, and the automated test suites.

## Troubleshooting

- If SDL3 fails to initialize, verify that your system meets the runtime
  requirements and that `SDL_GetError()` logs the failure cause inside
  `World::initializeSdl`. 【F:src/core/world.cpp†L19-L94】
- Missing UI overlays usually indicate the `UiManager::init` routine was not
  called; the world constructor handles this once SDL surfaces are ready. 【F:src/core/world.cpp†L96-L177】
- Physics behaving unexpectedly? Double-check mass, restitution, and gravity
  flags on each `Physics_Component` before stepping the simulation. 【F:src/physics/physics_component.h†L23-L59】
