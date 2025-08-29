//
// Created by AJYDAN on 21/05/2025.
//

#include "physics.h"
#include "core/entity.h"

void PhysicsSystem::update(std::vector<std::unique_ptr<Entity>>& entities, float dt, float ppm) {
	for (auto &entity : entities) {
		if (!entity || !entity->physics) {
			return;
		}

		float area = entity->shape->get_area_normalised(ppm);

		// Each physics component handles its own update logic
		entity->physics->update(dt,area );

	}
}


