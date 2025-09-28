# Architecture

## Engine Lifecycle

`World` is the top-level coordinator. Initialization wires up the renderer, collision dispatcher, SDL subsystems, the main window, and UI management before simulation begins.【F:src/core/world.h†L29-L60】【F:src/core/world.cpp†L22-L83】 The world keeps track of all entities, maintains collision state across frames, and exposes helpers to add single or batched entities.【F:src/core/world.h†L27-L56】【F:src/core/world.cpp†L42-L51】

Once running, each frame collects elapsed time, clears stale collision pairs, performs collision detection, advances physics, and finally renders both the scene and UI overlays.【F:src/core/world.cpp†L54-L206】 The renderer module draws each entity, while UI components render through the `UiManager` so overlays remain synchronized with the simulation.【F:src/core/world.cpp†L70-L206】

## Data Ownership

Entities own both their visual `Shape` and `Physics_Component` instances via `std::unique_ptr`, so the world can transfer ownership safely when spawning or batching entities.【F:src/core/entity.h†L22-L58】【F:src/core/world.cpp†L42-L51】 World-wide registries of currently and previously colliding entity IDs enable the engine to detect collision exits without storing transient per-entity flags.【F:src/core/world.h†L41-L58】【F:src/core/world.cpp†L148-L178】

## Module Boundaries

- **Core systems** define the world loop, entity model, and math utilities powering every module.【F:src/core/world.h†L24-L60】【F:src/core/vector.h†L8-L27】
- **Physics components** encapsulate motion logic and expose a uniform update signature consumed by the world.【F:src/physics/physics_component.h†L22-L63】【F:src/core/world.cpp†L119-L132】
- **Collision helpers** perform dispatch and resolution, invoked during the world's collision sweep before physics updates run.【F:src/collision/collision.h†L8-L27】【F:src/core/world.cpp†L142-L160】
- **Rendering** is isolated to the `Renderer` namespace so the world only needs to forward entities and the SDL renderer handle.【F:src/rendering/renderer.h†L12-L27】【F:src/core/world.cpp†L70-L83】
- **UI management** keeps transient UI actions and components outside the main world logic while still being triggered each frame.【F:src/ui/ui_manager.h†L24-L38】【F:src/core/world.cpp†L180-L206】
