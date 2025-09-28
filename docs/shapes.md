# Shapes

## Base Interface

`Shape` defines the common interface for all renderable geometries, including type identification, collider reporting, area computation, and a normalized area helper used by physics updates.【F:src/shapes/shape.h†L21-L33】 Shapes also track whether they participate in collisions so purely visual elements can opt out.【F:src/shapes/shape.h†L28-L33】

## Circle

`Circle` stores a radius and reports itself as a circular collider, supplying both absolute and pixels-per-meter normalized areas for use in physics calculations.【F:src/shapes/circle.h†L15-L30】 Radius getters and setters allow dynamic resizing at runtime.【F:src/shapes/circle.h†L24-L27】

## Rectangle

`Rectangle` keeps width and height dimensions, supports optional collider enablement, and implements AABB area calculations alongside normalized area output.【F:src/shapes/rectangle.h†L15-L34】 Use the provided accessors to tweak dimensions without rebuilding the entity.
