#include <gtest/gtest.h>
#include "physics/physics_component.h"

class PhysicsStub : public Physics_Component {
public:
    void update(float, float) override {}
    PhysicsType get_type() const override { return PhysicsType::NONE; }
};

TEST(PhysicsComponent, PositionSetGet) {
    PhysicsStub p;
    Vector2D pos{2.0f, -3.0f};
    p.set_position(pos);
    EXPECT_FLOAT_EQ(p.get_position().x, 2.0f);
    EXPECT_FLOAT_EQ(p.get_position().y, -3.0f);
}

TEST(PhysicsComponent, VelocitySetGet) {
    PhysicsStub p;
    Vector2D vel{5.0f, 4.0f};
    p.set_velocity(vel);
    EXPECT_FLOAT_EQ(p.get_velocity().x, 5.0f);
    EXPECT_FLOAT_EQ(p.get_velocity().y, 4.0f);
}

TEST(PhysicsComponent, StaticFlag) {
    PhysicsStub p;
    EXPECT_FALSE(p.is_static());
    p.set_static(true);
    EXPECT_TRUE(p.is_static());
}
