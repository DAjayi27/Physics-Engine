//
// Created by AJYDAN on 01/05/2025.
//

#include "vector.h"

float vector_add(Vector_2D point_a , Vector_2D point_b) {

}

Vector_2D vector_sub(Vector_2D point_a , Vector_2D point_b) {


    Vector_2D result;

    result.x = point_a.x - point_b.x;

    result.y = point_a.y - point_b.y;

    return result;

}


extern float vector_dist_sqr(Vector_2D point_a , Vector_2D point_b) {
    Vector_2D distance_vector = vector_sub(point_a,point_b);
    return ((distance_vector.x * distance_vector.x) + (distance_vector.y * distance_vector.y));
}

