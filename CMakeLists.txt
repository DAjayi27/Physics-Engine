cmake_minimum_required(VERSION 3.28.3)
project(Physics_Engine C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

find_package(SDL3 REQUIRED)
#find_package(SDL3_image REQUIRED)

add_executable(Physics_Engine
        src/main.cpp
        src/shapes/rectangle.cpp
        src/shapes/rectangle.h
        src/collision/collision.cpp
        src/collision/collision.h
        src/core/vector.cpp
        src/core/vector.h
        src/shapes/circle.cpp
        src/shapes/circle.h
        src/shapes/shape.cpp
        src/shapes/shape.h
        src/collision/collision_types.h
        src/physics/physics_component.cpp
        src/physics/physics_component.h
        src/physics/rigid_body.cpp
        src/physics/rigid_body.h
        src/core/entity.cpp
        src/core/entity.h
        src/physics/physics.cpp
        src/physics/physics.h
        src/rendering/renderer.cpp
        src/rendering/renderer.h
        src/physics/kinematic.cpp
        src/physics/kinematic.h
        src/physics/particle.cpp
        src/physics/particle.h
        src/engine/engine.h
        src/core/world.h
        src/core/world.cpp)

# Link SDL3 to the executable
#target_link_libraries(Physics_Engine SDL3_image::SDL3_image)
target_link_libraries(Physics_Engine SDL3::SDL3)
