#include "gtest/gtest.h"
#include "core/vector.h"


TEST(Vector2D, Addition) {
    Vector2D a = {1.0f, 2.0f};
    Vector2D b = {3.0f, 4.0f};
    Vector2D result = vector_add(a, b);
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST(Vector2D, Subtraction) {
    Vector2D a = {5.0f, 7.0f};
    Vector2D b = {2.0f, 3.0f};
    Vector2D result = vector_subtract(a, b);
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST(Vector2D, Scale) {
    Vector2D v = {2.0f, -3.0f};
    Vector2D result = vector_scale(v, 2.5f);
    EXPECT_FLOAT_EQ(result.x, 5.0f);
    EXPECT_FLOAT_EQ(result.y, -7.5f);
}

TEST(Vector2D, Magnitude) {
    Vector2D v = {3.0f, 4.0f};
    EXPECT_FLOAT_EQ(vector_magnitude(v), 5.0f);
}

TEST(Vector2D, MagnitudeSquared) {
    Vector2D v = {3.0f, 4.0f};
    EXPECT_FLOAT_EQ(vector_magnitude_squared(v), 25.0f);
}

TEST(Vector2D, Distance) {
    Vector2D a = {0.0f, 0.0f};
    Vector2D b = {0.0f, 5.0f};
    EXPECT_FLOAT_EQ(vector_distance(a, b), 5.0f);
}

TEST(Vector2D, DistanceSquared) {
    Vector2D a = {1.0f, 2.0f};
    Vector2D b = {4.0f, 6.0f};
    EXPECT_FLOAT_EQ(vector_distance_squared(a, b), 25.0f);
}

TEST(Vector2D, DotProduct) {
    Vector2D a = {1.0f, 3.0f};
    Vector2D b = {2.0f, 4.0f};
    EXPECT_FLOAT_EQ(vector_dot(a, b), 14.0f);
}

TEST(Vector2D, NormalizeNonZero) {
    Vector2D v = {3.0f, 4.0f};
    Vector2D n = vector_normalize(v);
    EXPECT_NEAR(n.x, 0.6f, 1e-5f);
    EXPECT_NEAR(n.y, 0.8f, 1e-5f);
}

TEST(Vector2D, NormalizeZero) {
    Vector2D v = {0.0f, 0.0f};
    Vector2D n = vector_normalize(v);
    EXPECT_FLOAT_EQ(n.x, 0.0f);
    EXPECT_FLOAT_EQ(n.y, 0.0f);
}

