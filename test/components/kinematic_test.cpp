#include <gtest/gtest.h>
#include "physics/kinematic.h"

TEST(Kinematic, DefaultsAndType) {
    Kinematic k;
    EXPECT_EQ(k.get_type(), PhysicsType::KINEMATIC);
    EXPECT_TRUE(k.is_affected_by_gravity());
}

TEST(Kinematic, AccelerationSetGet) {
    Kinematic k;
    Vector2D a{0.5f, 1.5f};
    k.set_acceleration(a);
    EXPECT_FLOAT_EQ(k.get_acceleration().x, 0.5f);
    EXPECT_FLOAT_EQ(k.get_acceleration().y, 1.5f);
}
