#include <gtest/gtest.h>
#include "physics/particle.h"

TEST(Particle, DefaultsAndType) {
    Particle p;
    EXPECT_EQ(p.get_type(), PhysicsType::PARTICLE);
    EXPECT_TRUE(p.is_affected_by_gravity());
    EXPECT_NEAR(p.get_mass(), 1.0f, 1e-5f);
}

TEST(Particle, LifetimeSetGetAndAlive) {
    Particle p;
    p.set_lifetime(0.5f);
    EXPECT_NEAR(p.get_lifetime(), 0.5f, 1e-6f);
    EXPECT_TRUE(p.is_alive());
}
