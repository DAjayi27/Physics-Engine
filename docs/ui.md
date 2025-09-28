# User Interface

## Manager Lifecycle

`UiManager` owns UI components, queues pending UI actions, and requires parent window/renderer pointers supplied during construction.【F:src/ui/ui_manager.h†L24-L38】 Initialization hooks set up default widgets, while `handleEvents` funnels SDL events through each component for processing.【F:src/ui/ui_manager.h†L33-L36】【F:src/core/world.cpp†L186-L206】

## UI Actions

UI interactions are expressed as `UIAction` structs describing the action type, target position, optional component, and RTTI tag, enabling deferred handling without tight coupling to specific widgets.【F:src/ui/ui_action.h†L17-L36】 Actions enter the manager's queue and are processed in batches so gameplay code can enqueue UI work from anywhere in the update loop.【F:src/ui/ui_manager.h†L29-L36】

## Components

The base `UiComponent` interface (see `components/ui_component.h`) exposes an event handler that returns actions. The included `PopupComponent` example renders an SDL window overlay and converts mouse events into open/close requests while tracking its own renderer and color palette.【F:src/ui/components/ui_popup.h†L12-L24】 During rendering, the world iterates active UI components so overlays draw after gameplay entities.【F:src/core/world.cpp†L196-L206】
