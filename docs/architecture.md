# Architecture

## Engine Lifecycle

`World` is the top-level coordinator. Initialization wires up the renderer, collision dispatcher, SDL subsystems, the main window, and UI management before simulation begins. The world keeps track of all entities, maintains collision state across frames, and exposes helpers to add single or batched entities.

Once running, each frame collects elapsed time, clears stale collision pairs, performs collision detection, advances physics, and finally renders both the scene and UI overlays.The renderer module draws each entity, while UI components render through the `UiManager` so overlays remain synchronized with the simulation.

## Data Ownership

Entities own both their visual `Shape` and `Physics_Component` instances via `std::unique_ptr`, so the world can transfer ownership safely when spawning or batching entities. World-wide registries of currently and previously colliding entity IDs enable the engine to detect collision exits without storing transient per-entity flags.

## Module Boundaries

- **Core systems** define the world loop, entity model, and math utilities powering every module.
- **Physics components** encapsulate motion logic and expose a uniform update signature consumed by the world.
- **Collision helpers** perform dispatch and resolution, invoked during the world's collision sweep before physics updates run.
- **Rendering** is isolated to the `Renderer` namespace so the world only needs to forward entities and the SDL renderer handle.
- **UI management** keeps transient UI actions and components outside the main world logic while still being triggered each frame.
