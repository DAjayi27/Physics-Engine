# Rendering

## Renderer Namespace

The `Renderer` namespace provides a minimal interface for drawing entities: `render_entity` accepts the entity, SDL renderer, optional texture, and a fill flag, while `initialize_render_system` configures any global SDL state before use.【F:src/rendering/renderer.h†L12-L27】 Entities are expected to expose their shapes and colors so the renderer can translate physics state into pixels.

## Frame Composition

During `World::render`, the engine clears the screen to a dark grey, draws each entity via `Renderer::render_entity`, and then lets UI components paint on top before swapping buffers.【F:src/core/world.cpp†L70-L83】【F:src/core/world.cpp†L196-L206】 This keeps gameplay visuals and overlays synchronized without duplicating SDL code across modules.
