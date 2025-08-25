#include <gtest/gtest.h>
#include "physics/rigid_body.h"

TEST(RigidBody, DefaultsAndType) {
    Rigid_Body rb;
    EXPECT_EQ(rb.get_type(), PhysicsType::RIGID_BODY);
    EXPECT_NEAR(rb.get_mass(), 1.0f, 1e-5f);
}

TEST(RigidBody, AccelerationSetGet) {
    Rigid_Body rb;
    Vector2D a{1.0f, -2.0f};
    rb.set_acceleration(a);
    EXPECT_FLOAT_EQ(rb.get_acceleration().x, 1.0f);
    EXPECT_FLOAT_EQ(rb.get_acceleration().y, -2.0f);
}

TEST(RigidBody, AffectedByGravityFlag) {
    Rigid_Body rb;
    EXPECT_TRUE(rb.is_affected_by_gravity());
    rb.set_affected_by_gravity(false);
    EXPECT_FALSE(rb.is_affected_by_gravity());
}

TEST(RigidBody, ApplyImpulseChangesVelocity) {
    Rigid_Body rb;
    rb.set_mass(2.0f);
    rb.set_velocity({0.0f, 0.0f});
    rb.apply_impulse({2.0f, 0.0f});
    // impulse / mass = delta_v
    EXPECT_FLOAT_EQ(rb.get_velocity().x, 1.0f);
}
