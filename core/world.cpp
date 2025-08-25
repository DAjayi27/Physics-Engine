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
	initialize_collision_system();
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

	this->check_collisions();
	this->update_physics_simulation(delta_time);

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
void World::check_collisions() {

	for (size_t i = 0; i < entities.size(); ++i) {
		for (size_t j = i + 1; j < entities.size(); ++j) {

			auto& entity_a = entities[i];
			auto& entity_b = entities[j];

			Vector2D collision_normal = is_colliding( entity_a.get(), entity_b.get() );

			if ( collision_normal.x != 0 || collision_normal.y != 0   ) {

				handle_collision(entity_a.get(), entity_b.get(),collision_normal);

				currently_colliding_entities.insert(this->generate_pairing(entity_a->entity_id , entity_b->entity_id));
				continue;
			}


			handle_collision_exit(entity_a,entity_b);

		}
	}

}

uint64_t World:: generate_pairing (uint32_t first_id ,  uint32_t second_id) {
	return (uint64_t)std::min(first_id,second_id) << 32 | std::max(first_id,second_id);
}

void World::handle_collision_exit(unique_ptr<Entity>& entity_a , unique_ptr<Entity>& entity_b ) {

	uint64_t paired_id = this->generate_pairing(entity_a->entity_id , entity_b->entity_id);

	if (prev_colliding_entities.contains(paired_id)) {
		((Rigid_Body*)entity_a->physics.get())->set_affected_by_gravity(true);
		((Rigid_Body*)entity_b->physics.get())->set_affected_by_gravity(true);
	}

}



