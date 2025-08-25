#include <gtest/gtest.h>
#include "collision/collision.h"
#include "shapes/circle.h"
#include "physics/rigid_body.h"

static Entity makeCircleEntity(uint64_t id, float x, float y, float r) {
    auto shape = std::make_unique<Circle>(r);
    auto phys = std::make_unique<Rigid_Body>();
    phys->set_position({x, y});
    Entity e(id, std::move(shape), std::move(phys), SDL_Color{255,255,255,255});
    e.collision_type = CIRCLE_COLLISION;
    return e;
}

TEST(Collision, AabbCollisionSeparatingAxis) {
    auto a = makeCircleEntity(1, 0.0f, 0.0f, 10.0f);
    auto b = makeCircleEntity(2, 100.0f, 100.0f, 10.0f);
    Vector2D n = aabb_collision(&a, &b);
    EXPECT_FLOAT_EQ(n.x, 0.0f);
    EXPECT_FLOAT_EQ(n.y, 0.0f);
}

TEST(Collision, IsCollidingReturnsNormalOnOverlap) {
    auto a = makeCircleEntity(1, 0.0f, 0.0f, 10.0f);
    auto b = makeCircleEntity(2, 5.0f, 0.0f, 10.0f);
    Vector2D n = is_colliding(&a, &b);
    EXPECT_TRUE(n.x != 0.0f || n.y != 0.0f);
}
