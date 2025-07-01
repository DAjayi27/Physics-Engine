//
// Created by AJYDAN on 01/07/2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "core/vector.h"

typedef struct {
    Vector_2D velocity;
    Vector_2D acceleration;
    float lifetime;
    float mass;
} Particle_Body;


#endif //PARTICLE_H
