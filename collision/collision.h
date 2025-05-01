//
// Created by AJYDAN on 01/05/2025.
//

#ifndef COLLISION_H
#define COLLISION_H

typedef enum {
    NONE,
    CIRCLE_COLLISION,
    AABB_COLLISION

} Collision_Type;

typedef struct {
    Collision_Type type;
    union {

    };

}Collider;

#endif //COLLISION_H
