# Shapes

## Base Interface

`Shape` defines the common interface for all renderable geometries, including type identification, collider reporting, area computation, and a normalized area helper used by physics updates. Shapes also track whether they participate in collisions so purely visual elements can opt out.

## Circle

`Circle` stores a radius and reports itself as a circular collider, supplying both absolute and pixels-per-meter normalized areas for use in physics calculations. Radius getters and setters allow dynamic resizing at runtime.

## Rectangle

`Rectangle` keeps width and height dimensions, supports optional collider enablement, and implements AABB area calculations alongside normalized area output. Use the provided accessors to tweak dimensions without rebuilding the entity.
