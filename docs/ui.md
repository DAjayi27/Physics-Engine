# User Interface

## Manager Lifecycle

`UiManager` owns UI components, queues pending UI actions, and requires parent window/renderer pointers supplied during construction. Initialization hooks set up default widgets, while `handleEvents` funnels SDL events through each component for processing.

## UI Actions

UI interactions are expressed as `UIAction` structs describing the action type, target position, optional component, and RTTI tag, enabling deferred handling without tight coupling to specific widgets. Actions enter the manager's queue and are processed in batches so gameplay code can enqueue UI work from anywhere in the update loop.

## Components

The base `UiComponent` interface (see `components/ui_component.h`) exposes an event handler that returns actions. The included `PopupComponent` example renders an SDL window overlay and converts mouse events into open/close requests while tracking its own renderer and color palette. During rendering, the world iterates active UI components so overlays draw after gameplay entities.
