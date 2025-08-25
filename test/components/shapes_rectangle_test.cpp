#include <gtest/gtest.h>
#include "shapes/rectangle.h"

TEST(RectangleShape, DefaultsAndArea) {
    Rectangle r(4.0f, 3.0f);
    EXPECT_EQ(r.get_type(), ShapeType::RECTANGLE);
    EXPECT_EQ(r.get_collision_type(), AABB_COLLISION);
    EXPECT_FLOAT_EQ(r.get_area(), 12.0f);
}

TEST(RectangleShape, WidthHeightSetGet) {
    Rectangle r(1.0f, 2.0f);
    r.set_width(5.0f);
    r.set_height(7.0f);
    EXPECT_FLOAT_EQ(r.get_width(), 5.0f);
    EXPECT_FLOAT_EQ(r.get_height(), 7.0f);
}

TEST(RectangleShape, AreaNormalised) {
    Rectangle r(100.0f, 50.0f);
    int ppm = 50;
    float expected = r.get_area() / (ppm * ppm);
    EXPECT_NEAR(r.get_area_normalised(ppm), expected, 1e-4f);
}
