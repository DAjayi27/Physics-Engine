// physics/physics_system.h
#pragma once
#include <memory>
#include <vector>
class Entity;

class PhysicsSystem {
public:
	void update(std::vector<std::unique_ptr<Entity>>& entities, float dt, float ppm);
};
