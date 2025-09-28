# Physics Engine

A modular 2D physics sandbox written in modern C++ and rendered with SDL3. The
engine bundles rigid body dynamics, collision detection, and a lightweight UI
layer into a single component-based architecture that is easy to extend for
experiments or teaching demos.

## Features

- **Entity-component design** – Every `Entity` owns a renderable `Shape` and a
  `Physics_Component`, letting you mix rigid bodies, particles, or kinematic
  actors in the same world.
- **Deterministic physics integration** – `Rigid_Body`, `Particle`, and
  `Kinematic` components expose friction, restitution, and gravity controls so
  that simulations remain stable across frame rates.
- **Collision system with resolution** – Circle and rectangle shapes can be
  checked with broad-phase AABB tests before dispatching to collision
  resolution routines.
- **SDL3 rendering pipeline** – `Renderer::render_entity` draws world entities
  and UI overlays using SDL textures and primitive drawing.
- **UI actions and overlays** – The `UiManager` manages popup components and
  queues UI actions triggered during the simulation loop.
- **Extensive automated tests** – Component and UI integration tests cover
  vector math, physics updates, collision handling, and world orchestration via
  GoogleTest.


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
- **CMake 3.28** or newer.
- **SDL3 development libraries** discoverable via `find_package(SDL3 REQUIRED)`.
- (Optional) `SDL3_image` if you enable the commented texture loading hooks.

GoogleTest is fetched automatically through `FetchContent`, so no system-wide
installation is required.

## Building the Project

```bash
cmake -S . -B build
cmake --build build
```

The default target compiles the `Physics_Engine` executable along with two test
runners:

- `Physics_Engine_Component_Tests` for headless unit tests.
- `Physics_Engine_UI_Tests` for SDL-driven integration checks.

All targets link against SDL3 and are generated in the chosen build directory.

## Running the Simulation

1. Build the project.
2. Ensure SDL3 can create a window on your platform (e.g., X11, Wayland,
   or Windows/macOS desktop session).
3. Launch the executable:

   ```bash
   ./build/Physics_Engine
   ```

The main loop (`World::update`) handles SDL events, processes UI actions, runs physics, and renders entities each frame. Use the
arrow keys to nudge the selected entity around (`handle_input` in `main.cpp`).

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
will automatically enumerate the GoogleTest cases.

## Extending the Engine

- **Add a new shape** by subclassing `Shape`, implementing `get_type`,`get_bounds`, and `render`, then composing it into an `Entity`. 【F:src/shapes/shape.h†L8-L44】
- **Create a custom physics component** by deriving from
  `Physics_Component`, overriding `update`, and exposing configuration knobs
  similar to `Rigid_Body`.
- **Hook UI controls** by creating a `UiComponent` and pushing `UIAction`
  instances onto the manager queue.

Because the world stores entities as `std::unique_ptr`, ownership stays clear
and components can share data through simple pointers or events.

## Detailed Documentation

Additional module-by-module guides live in [`docs/`](docs/README.md), covering
architecture, core systems, physics, collision detection, shapes, rendering,
UI, and the automated test suites.

## Troubleshooting

- If SDL3 fails to initialize, verify that your system meets the runtime
  requirements and that `SDL_GetError()` logs the failure cause inside
  `World::initializeSdl`.
- Missing UI overlays usually indicate the `UiManager::init` routine was not
  called; the world constructor handles this once SDL surfaces are ready.
- Physics behaving unexpectedly? Double-check mass, restitution, and gravity
  flags on each `Physics_Component` before stepping the simulation.