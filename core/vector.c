//
// Created by AJYDAN on 01/05/2025.
//

#include "vector.h"

extern Vector_2D vector_add(Vector_2D vector_a , Vector_2D vector_b) {

    Vector_2D result;

    result.x = vector_a.x + vector_b.x;
    result.y = vector_a.y + vector_b.y;

    return result;
}


extern Vector_2D vector_scale(Vector_2D vector_a , float scale) {

    Vector_2D result;

    result.x = vector_a.x * scale;
    result.y = vector_a.y * scale;

    return result;
}

Vector_2D vector_sub(Vector_2D vector_a , Vector_2D vector_b) {


    Vector_2D result;

    result.x = vector_a.x - vector_b.x;

    result.y = vector_a.y - vector_b.y;

    return result;

}


extern float vector_dist_sqr(Vector_2D vector_a , Vector_2D vector_b) {
    Vector_2D distance_vector = vector_sub(vector_a,vector_b);
    return ((distance_vector.x * distance_vector.x) + (distance_vector.y * distance_vector.y));
}

