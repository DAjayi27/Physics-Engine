//
// Created by AJYDAN on 01/05/2025.
//

#include "vector.h"
#include <math.h>

/**
 * @brief Adds two vectors together
 * @param a First vector
 * @param b Second vector
 * @return Result of a + b
 */
Vector2D vector_add(Vector2D a, Vector2D b) {
    Vector2D result = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
    return result;
}

/**
 * @brief Subtracts vector b from vector a
 * @param a First vector
 * @param b Second vector
 * @return Result of a - b
 */
Vector2D vector_subtract(Vector2D a, Vector2D b) {
    Vector2D result = {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
    return result;
}

/**
 * @brief Scales a vector by a scalar value
 * @param vector Vector to scale
 * @param scalar Scalar value to multiply by
 * @return Result of vector * scalar
 */
Vector2D vector_scale(Vector2D vector, float scalar) {
    Vector2D result = {
        .x = vector.x * scalar,
        .y = vector.y * scalar
    };
    return result;
}

/**
 * @brief Calculates the magnitude (length) of a vector
 * @param vector Vector to calculate magnitude for
 * @return Magnitude of the vector
 */
float vector_magnitude(Vector2D vector) {
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

/**
 * @brief Calculates the squared magnitude of a vector (faster than magnitude)
 * @param vector Vector to calculate squared magnitude for
 * @return Squared magnitude of the vector
 */
float vector_magnitude_squared(Vector2D vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

/**
 * @brief Calculates the distance between two points
 * @param a First point
 * @param b Second point
 * @return Distance between the points
 */
float vector_distance(Vector2D a, Vector2D b) {
    Vector2D diff = vector_subtract(a, b);
    return vector_magnitude(diff);
}

/**
 * @brief Calculates the squared distance between two points (faster than distance)
 * @param a First point
 * @param b Second point
 * @return Squared distance between the points
 */
float vector_distance_squared(Vector2D a, Vector2D b) {
    Vector2D diff = vector_subtract(a, b);
    return vector_magnitude_squared(diff);
}

/**
 * @brief Calculates the dot product of two vectors
 * @param a First vector
 * @param b Second vector
 * @return Dot product of a and b
 */
float vector_dot(Vector2D a, Vector2D b) {
    return a.x * b.x + a.y * b.y;
}

/**
 * @brief Normalizes a vector (makes it unit length)
 * @param vector Vector to normalize
 * @return Normalized vector, or zero vector if input is zero
 */
Vector2D vector_normalize(Vector2D vector) {
    float mag = vector_magnitude(vector);
    if (mag > 0.0f) {
        return vector_scale(vector, 1.0f / mag);
    }
    return (Vector2D){0.0f, 0.0f};
}

