#include <gtest/gtest.h>
#include <memory>
#include "core/entity.h"
#include "shapes/circle.h"
#include "physics/rigid_body.h"

class EntityTest : public ::testing::Test {
protected:
    std::unique_ptr<Shape> shape = std::make_unique<Circle>(1.0f);
    std::unique_ptr<Physics_Component> physics = std::make_unique<Rigid_Body>();
    SDL_Color color{255, 0, 0, 255};
};

TEST_F(EntityTest, DefaultConstructorInitializesFields) {
    Entity e;
    EXPECT_EQ(e.get_position().x, 0.0f);
    EXPECT_EQ(e.get_position().y, 0.0f);
    EXPECT_EQ(e.get_velocity().x, 0.0f);
    EXPECT_EQ(e.get_velocity().y, 0.0f);
    EXPECT_FALSE(e.is_static());
}

TEST_F(EntityTest, SetAndGetPosition) {
    Entity e(1, std::make_unique<Circle>(2.0f), std::make_unique<Rigid_Body>(), color);
    Vector2D pos = {3.0f, 4.0f};
    e.set_position(pos);
    EXPECT_FLOAT_EQ(e.get_position().x, 3.0f);
    EXPECT_FLOAT_EQ(e.get_position().y, 4.0f);
}

TEST_F(EntityTest, SetAndGetVelocity) {
    Entity e(2, std::make_unique<Circle>(2.0f), std::make_unique<Rigid_Body>(), color);
    Vector2D vel = {5.0f, -2.0f};
    e.set_velocity(vel);
    EXPECT_FLOAT_EQ(e.get_velocity().x, 5.0f);
    EXPECT_FLOAT_EQ(e.get_velocity().y, -2.0f);
}

TEST_F(EntityTest, SetPositionXAndY) {
    Entity e(3, std::make_unique<Circle>(2.0f), std::make_unique<Rigid_Body>(), color);
    e.set_position({0.0f, 0.0f});
    e.set_position_x(7.0f);
    e.set_position_y(-3.0f);
    EXPECT_FLOAT_EQ(e.get_position().x, 7.0f);
    EXPECT_FLOAT_EQ(e.get_position().y, -3.0f);
}

TEST_F(EntityTest, SetVelocityXAndY) {
    Entity e(4, std::make_unique<Circle>(2.0f), std::make_unique<Rigid_Body>(), color);
    e.set_velocity({0.0f, 0.0f});
    e.set_velocity_x(2.5f);
    e.set_velocity_y(-1.5f);
    EXPECT_FLOAT_EQ(e.get_velocity().x, 2.5f);
    EXPECT_FLOAT_EQ(e.get_velocity().y, -1.5f);
}

TEST_F(EntityTest, IsStaticReturnsTrueWhenPhysicsIsStatic) {
    Entity e(5, std::make_unique<Circle>(2.0f), std::make_unique<Rigid_Body>(), color);
    e.set_static(true);
    EXPECT_TRUE(e.is_static());
}

TEST_F(EntityTest, GetPositionReturnsZeroIfNoPhysics) {
    Entity e;
    e.physics = nullptr;
    Vector2D pos = e.get_position();
    EXPECT_FLOAT_EQ(pos.x, 0.0f);
    EXPECT_FLOAT_EQ(pos.y, 0.0f);
}

