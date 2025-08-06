#include "world.h"

#include "collision/collision.h"
#include "physics/rigid_body.h"
#include "rendering/renderer.h"

World::World() {

	this->entity_count = 0;
	this->window = nullptr;
	this->renderer = nullptr;
}

bool World::init() {

	Renderer::initialize_render_system();
	if (!initialize_sdl()) {
		return false;
	}
	init_window_and_renderer(&this->window, &this->renderer);
	return true;
}

bool World::quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return true;
}


void World::addEntity(unique_ptr<Entity> entity) {
	this->entities.push_back(move(entity));
	this->entity_count++;
}

void World::addEntities(vector<unique_ptr<Entity>>& entities) {
	for (auto& entity : entities) {
		addEntity(move(entity));
	}
}


void World::update() {

	uint64_t current_time = SDL_GetPerformanceCounter();
	float delta_time = (float)(current_time - last_time) / (float)SDL_GetPerformanceFrequency();
	last_time = current_time;

	if (!this->currently_colliding_entities.empty()) {
		this->prev_colliding_entities  = this->currently_colliding_entities;
		this->currently_colliding_entities.clear();
	}

	update_physics_simulation(delta_time);

}

void World::render() {

	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	for (auto&entity : entities) {
		Renderer::render_entity(entity.get(),renderer,nullptr,false);
	}
	SDL_RenderPresent(renderer);
}

/**
 * @brief Initializes SDL and returns success status
 * @return true if initialization failed, false if successful
 */
bool World::initialize_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		return true;
	} else {
		SDL_Log("SDL Failed To initialize %s", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}
}

/**
 * @brief Initializes the SDL window and renderer
 * @param window Pointer to SDL_Window* to be initialized
 * @param renderer Pointer to SDL_Renderer* to be initialized
 */
void World::init_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer) {
	SDL_Rect bounds;
	SDL_GetDisplayBounds(2, &bounds);

	*window = SDL_CreateWindow("Physics Engine", 1920, 1080, 0);
	SDL_SetWindowPosition(*window, bounds.x, bounds.y);
	*renderer = SDL_CreateRenderer(*window, "opengl");
	SDL_SetRenderVSync(*renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
}

/**
 * @brief Updates physics for an array of entities
 * @param entities Array of entities to update
 * @param delta_time Time elapsed since last frame
 */
void World::update_physics_simulation(float delta_time) {

	for (auto &entity : entities) {
		if (!entity || !entity->physics) {
			return;
		}

		float area = entity->shape->get_area_normalised(PPM);

		// Each physics component handles its own update logic
		entity->physics->update(delta_time,area );

	}
}

/**
 * @brief Checks for collisions between entities
 * @param entities Array of entities to check
 * @param count Number of entities
 * @param delta_time Time elapsed since last frame
 */
void World::check_collisions(float delta_timem ) {

	for (size_t i = 0; i < entities.size(); ++i) {
		for (size_t j = i + 1; j < entities.size(); ++j) {

			auto& entity_a = entities[i];
			auto& entity_b = entities[j];

			if (is_colliding(entity_a.get(), entity_b.get())) {
				handle_collision(entity_a.get(), entity_b.get());
				Colliding_Entities entry(entity_a.get(), entity_b.get());
				currently_colliding_entities.push_back(entry);
				continue;
			}

			Colliding_Entities tuple(entity_a.get(), entity_b.get());

			auto iterator = find_if(prev_colliding_entities.begin(), prev_colliding_entities.end(),
				[&tuple](Colliding_Entities& entry) {
						bool first_is_same = std::get<0>(entry) == std::get<0>(tuple);
						bool second_is_same = std::get<1>(entry) == std::get<1>(tuple);
						return first_is_same && second_is_same;
				}
			);

			if (iterator != prev_colliding_entities.end()) {
				((Rigid_Body*)entity_a->physics.get())->set_affected_by_gravity(true);
				((Rigid_Body*)entity_b->physics.get())->set_affected_by_gravity(true);
			}
		}
	}
}



