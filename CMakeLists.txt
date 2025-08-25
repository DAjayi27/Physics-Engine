cmake_minimum_required(VERSION 3.28.3)
project(Physics_Engine C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(SDL3 REQUIRED)
#find_package(SDL3_image REQUIRED)

enable_testing()

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
        src/core/world.cpp
        src/ui/ui_popup.cpp
        src/ui/ui_popup.h
        src/ui/ui_component.cpp
        src/ui/ui_component.h
        src/core/ui_manager.cpp
        src/core/ui_manager.h)

# Link SDL3 to the app
#target_link_libraries(Physics_Engine SDL3_image::SDL3_image)
target_link_libraries(Physics_Engine SDL3::SDL3)

# Component tests (pure unit tests, no windowing)
add_executable(Physics_Engine_Component_Tests
        test/components/vector2d_test.cpp
        test/components/entity_test.cpp
        test/components/shapes_circle_test.cpp
        test/components/shapes_rectangle_test.cpp
        test/components/physics_component_test.cpp
        test/components/rigid_body_test.cpp
        test/components/kinematic_test.cpp
        test/components/particle_test.cpp
        test/components/physics_update_test.cpp
        test/components/collision_test.cpp

        src/core/vector.cpp
        src/core/vector.h
        src/shapes/circle.cpp
        src/shapes/circle.h
        src/shapes/rectangle.cpp
        src/shapes/rectangle.h
        src/shapes/shape.cpp
        src/shapes/shape.h
        src/collision/collision.cpp
        src/collision/collision.h
        src/collision/collision_types.h
        src/physics/physics_component.cpp
        src/physics/physics_component.h
        src/physics/rigid_body.cpp
        src/physics/rigid_body.h
        src/physics/kinematic.cpp
        src/physics/kinematic.h
        src/physics/particle.cpp
        src/physics/particle.h
        src/physics/physics.cpp
        src/physics/physics.h
        src/core/entity.cpp
        src/core/entity.h
)

target_link_libraries(Physics_Engine_Component_Tests GTest::gtest_main SDL3::SDL3)

# UI/Integration tests (windowing, rendering, SDL lifecycle)
add_executable(Physics_Engine_UI_Tests
        test/ui/world_test.cpp

        src/core/world.cpp
        src/core/world.h
        src/core/vector.cpp
        src/core/vector.h
        src/shapes/circle.cpp
        src/shapes/circle.h
        src/shapes/rectangle.cpp
        src/shapes/rectangle.h
        src/shapes/shape.cpp
        src/shapes/shape.h
        src/collision/collision.cpp
        src/collision/collision.h
        src/collision/collision_types.h
        src/physics/physics_component.cpp
        src/physics/physics_component.h
        src/physics/rigid_body.cpp
        src/physics/rigid_body.h
        src/physics/kinematic.cpp
        src/physics/kinematic.h
        src/physics/particle.cpp
        src/physics/particle.h
        src/physics/physics.cpp
        src/physics/physics.h
        src/core/entity.cpp
        src/core/entity.h
        src/rendering/renderer.cpp
        src/rendering/renderer.h
        src/ui/ui_popup.cpp
        src/ui/ui_popup.h
)

target_link_libraries(Physics_Engine_UI_Tests GTest::gtest_main SDL3::SDL3)

# UI/Integration tests (windowing, rendering, SDL lifecycle)
add_executable(Physics_Engine_ALL_TESTS
        test/ui/world_test.cpp
        test/components/vector2d_test.cpp
        test/components/entity_test.cpp
        test/components/shapes_circle_test.cpp
        test/components/shapes_rectangle_test.cpp
        test/components/physics_component_test.cpp
        test/components/rigid_body_test.cpp
        test/components/kinematic_test.cpp
        test/components/particle_test.cpp
        test/components/physics_update_test.cpp
        test/components/collision_test.cpp

        src/core/world.cpp
        src/core/world.h
        src/core/vector.cpp
        src/core/vector.h
        src/shapes/circle.cpp
        src/shapes/circle.h
        src/shapes/rectangle.cpp
        src/shapes/rectangle.h
        src/shapes/shape.cpp
        src/shapes/shape.h
        src/collision/collision.cpp
        src/collision/collision.h
        src/collision/collision_types.h
        src/physics/physics_component.cpp
        src/physics/physics_component.h
        src/physics/rigid_body.cpp
        src/physics/rigid_body.h
        src/physics/kinematic.cpp
        src/physics/kinematic.h
        src/physics/particle.cpp
        src/physics/particle.h
        src/physics/physics.cpp
        src/physics/physics.h
        src/core/entity.cpp
        src/core/entity.h
        src/rendering/renderer.cpp
        src/rendering/renderer.h
        src/ui/ui_popup.cpp
        src/ui/ui_popup.h
)

target_link_libraries(Physics_Engine_ALL_TESTS GTest::gtest_main SDL3::SDL3)

include(GoogleTest)
gtest_discover_tests(Physics_Engine_Component_Tests)
gtest_discover_tests(Physics_Engine_UI_Tests)