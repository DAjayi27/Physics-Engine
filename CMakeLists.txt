cmake_minimum_required(VERSION 3.28.3)
project(Physics_Engine C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(Physics_Engine
    main.c
        shapes/rectangle.c
        shapes/rectangle.h
        collision/collision.c
        collision/collision.h
        core/vector.c
        core/vector.h
        shapes/circle.c
        shapes/circle.h
        shapes/shape.c
        shapes/shape.h
        collision/collision_types.h
        physics/physics_component.c
        physics/physics_component.h
        physics/rigid_body.c
        physics/rigid_body.h
        core/entity.c
        core/entity.h
        physics/physics.c
        physics/physics.h
        rendering/renderer.c
        rendering/renderer.h)

# Link SDL3 to the executable
target_link_libraries(Physics_Engine SDL3_image::SDL3_image)
target_link_libraries(Physics_Engine SDL3::SDL3)
