//
// Created by AJYDAN on 01/05/2025.
//

#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector_2D Vector_2D;

struct Vector_2D{
    float x;
    float y;
};


extern float vector_dist_sqr(Vector_2D point_a , Vector_2D point_b);

extern Vector_2D vector_add(Vector_2D point_a , Vector_2D point_b);

extern Vector_2D vector_scale(Vector_2D point_a , float scale);

#endif //VECTOR_H
