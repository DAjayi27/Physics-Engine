cmake_minimum_required(VERSION 3.28.3)
project(Physics_Engine C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(Physics_Engine
        main.cpp
        shapes/rectangle.cpp
        shapes/rectangle.h
        collision/collision.cpp
        collision/collision.h
        core/vector.cpp
        core/vector.h
        shapes/circle.cpp
        shapes/circle.h
        shapes/shape.cpp
        shapes/shape.h
        collision/collision_types.h
        physics/physics_component.cpp
        physics/physics_component.h
        physics/rigid_body.cpp
        physics/rigid_body.h
        core/entity.cpp
        core/entity.h
        physics/physics.cpp
        physics/physics.h
        rendering/renderer.cpp
        rendering/renderer.h
        physics/kinematic.cpp
        physics/kinematic.h
        physics/particle.cpp
        physics/particle.h
        engine/engine.h)

# Link SDL3 to the executable
target_link_libraries(Physics_Engine SDL3_image::SDL3_image)
target_link_libraries(Physics_Engine SDL3::SDL3)
