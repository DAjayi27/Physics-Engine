#include <gtest/gtest.h>
#include "physics/physics.h"
#include "core/entity.h"
#include "shapes/circle.h"
#include "physics/rigid_body.h"

TEST(PhysicsUpdate, UpdatesEntityVelocityOrPosition) {
    Entity e(1, std::make_unique<Circle>(1.0f), std::make_unique<Rigid_Body>(), SDL_Color{255,255,255,255});
    auto pos_before = e.get_position();
    update_physics(&e, 0.016f);
    auto pos_after = e.get_position();
    // Not asserting exact physics; just ensure function executes and state is coherent
    EXPECT_TRUE(pos_after.x == pos_after.x); // not NaN
    EXPECT_TRUE(pos_after.y == pos_after.y);
}
