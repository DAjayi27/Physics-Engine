// core/entity.cpp

#include "entity.h"

#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "physics/rigid_body.h"
#include "physics/kinematic.h"
#include "physics/particle.h"

Entity::Entity() 
    : shape(nullptr)
    , physics(nullptr)
    , color{0, 0, 0, 255}
    , collision_type(NONE) {
}

Entity::Entity(std::unique_ptr<Shape> shape, 
               std::unique_ptr<Physics_Component> physics, 
               SDL_Color color)
    : shape(std::move(shape))
    , physics(std::move(physics))
    , color(color)
    , collision_type(NONE) {
}

Vector2D Entity::get_position() const {
    return physics ? physics->get_position() : Vector2D{0.0f, 0.0f};
}

void Entity::set_position(Vector2D position) {
    if (physics) {
        physics->set_position(position);
    }
}

void Entity::set_position_x(float x) {
    if (physics) {
        physics->set_position_x(x);
    }
}

void Entity::set_position_y(float y) {
    if (physics) {
        physics->set_position_y(y);
    }
}

Vector2D Entity::get_velocity() const {
    return physics ? physics->get_velocity() : Vector2D{0.0f, 0.0f};
}

void Entity::set_velocity(Vector2D velocity) {
    if (physics) {
        physics->set_velocity(velocity);
    }
}

void Entity::set_velocity_x(float x) {
    if (physics) {
        physics->set_velocity_x(x);
    }
}

void Entity::set_velocity_y(float y) {
    if (physics) {
        physics->set_velocity_y(y);
    }
}

bool Entity::is_static() const {
    return physics ? physics->is_static() : true;
}

void Entity::set_static(bool is_static) {
    if (physics) {
        physics->set_static(is_static);
    }
}

// Entity factory functions
Entity create_circle_entity(float x, float y, float radius, SDL_Color color, 
                           PhysicsType physics_type, float mass) {
    auto shape = std::make_unique<Circle>(radius);
    std::unique_ptr<Physics_Component> physics;
    
    switch (physics_type) {
        case PhysicsType::RIGID_BODY:
            physics = std::make_unique<Rigid_Body>(mass, 0.1f, 0.5f, 
                                                  Vector2D{0.0f, 0.0f}, 
                                                  Vector2D{0.0f, 0.0f}, 
                                                  false, true);
            break;
        case PhysicsType::KINEMATIC:
            physics = std::make_unique<Kinematic>(mass, Vector2D{0.0f, 0.0f}, 
                                                 Vector2D{0.0f, 0.0f}, 
                                                 false, true);
            break;
        case PhysicsType::PARTICLE:
            physics = std::make_unique<Particle>(mass, Vector2D{0.0f, 0.0f}, 
                                                1.0f, false);
            break;
        default:
            physics = std::make_unique<Rigid_Body>();
            break;
    }
    
    physics->set_position(Vector2D{x, y});
    
    Entity entity(std::move(shape), std::move(physics), color);
    entity.collision_type = CIRCLE_COLLISION;
    return entity;
}

Entity create_rectangle_entity(float x, float y, float width, float height, 
                              bool is_static, SDL_Color color) {
    auto shape = std::make_unique<Rectangle>(width, height, true);
    auto physics = std::make_unique<Rigid_Body>(1.0f, 0.1f, 0.5f, 
                                               Vector2D{0.0f, 0.0f}, 
                                               Vector2D{0.0f, 0.0f}, 
                                               is_static, false);
    
    physics->set_position(Vector2D{x, y});
    
    Entity entity(std::move(shape), std::move(physics), color);
    entity.collision_type = AABB_COLLISION;
    return entity;
}



