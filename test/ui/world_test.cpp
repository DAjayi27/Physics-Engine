#include <gtest/gtest.h>
#include <memory>
#include "core/world.h"
#include "core/entity.h"
#include "shapes/circle.h"
#include "physics/rigid_body.h"

class WorldTest : public ::testing::Test {
protected:
    World world;
};

TEST_F(WorldTest, AddEntityIncreasesCount) {
    int initial_count = world.entity_count;
    auto entity = std::make_unique<Entity>(1, std::make_unique<Circle>(1.0f), std::make_unique<Rigid_Body>(), SDL_Color{255,0,0,255});
    world.addEntity(std::move(entity));
    EXPECT_EQ(world.entity_count, initial_count + 1);
}

TEST_F(WorldTest, AddEntitiesIncreasesCount) {
    int initial_count = world.entity_count;
    std::vector<std::unique_ptr<Entity>> entities;
    for (int i = 0; i < 3; ++i) {
        entities.push_back(std::make_unique<Entity>(i, std::make_unique<Circle>(1.0f), std::make_unique<Rigid_Body>(), SDL_Color{255,0,0,255}));
    }
    world.addEntities(entities);
    EXPECT_EQ(world.entity_count, initial_count + 3);
}

TEST_F(WorldTest, InitReturnsTrue) {
    EXPECT_TRUE(world.init());
    world.quit();
}

TEST_F(WorldTest, QuitReturnsTrue) {
    world.init();
    EXPECT_TRUE(world.quit());
}
