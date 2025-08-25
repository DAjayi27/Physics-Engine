#include <gtest/gtest.h>
#include "shapes/circle.h"

TEST(CircleShape, DefaultsAndArea) {
    Circle c(2.0f);
    EXPECT_EQ(c.get_type(), ShapeType::CIRCLE);
    EXPECT_EQ(c.get_collision_type(), CIRCLE_COLLISION);
    const float pi = 3.14159265358979323846f;
    EXPECT_NEAR(c.get_area(), pi * 4.0f, 1e-4f);
}

TEST(CircleShape, RadiusSetGet) {
    Circle c(1.0f);
    c.set_radius(3.5f);
    EXPECT_FLOAT_EQ(c.get_radius(), 3.5f);
}

TEST(CircleShape, AreaNormalised) {
    Circle c(10.0f);
    int ppm = 50;
    float expected = c.get_area() / (ppm * ppm);
    EXPECT_NEAR(c.get_area_normalised(ppm), expected, 1e-4f);
}
