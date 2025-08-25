//
// Created by AJYDAN on 01/05/2025.
//

#pragma once

/**
 * @brief 2D vector structure for mathematical operations
 */
typedef struct Vector2D {
    float x;
    float y;
} Vector2D;

// Legacy compatibility
typedef Vector2D Vector_2D;

// Vector operations
Vector2D vector_add(Vector2D a, Vector2D b);
Vector2D vector_subtract(Vector2D a, Vector2D b);
Vector2D vector_scale(Vector2D vector, float scalar);
float vector_magnitude(Vector2D vector);
float vector_magnitude_squared(Vector2D vector);
float vector_distance(Vector2D a, Vector2D b);
float vector_distance_squared(Vector2D a, Vector2D b);
float vector_dot(Vector2D a, Vector2D b);
Vector2D vector_normalize(Vector2D vector);

// Legacy function names for compatibility
#define vector_dist_sqr vector_distance_squared
