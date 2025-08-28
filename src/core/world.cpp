#include "world.h"

#include "collision/collision.h"
#include "physics/rigid_body.h"
#include "rendering/renderer.h"
#include <iostream>

#include "ui/components/ui_popup.h"

#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 1}
#define WHITE (SDL_Color){255, 255, 255, 255}

World::World(                        ) {

	this->entity_count = 0;
	this->window = nullptr;
	this->renderer = nullptr;
	this->ui_manager = nullptr;
}

bool World::init() {

	Renderer::initialize_render_system();
	initialize_collision_system();
	if (!initializeSdl()) {
		return false;
	}
	this->initWindowAndRenderer(&this->window, &this->renderer);
	this->initialiseUiManager();
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

	this->checkCollisions();
	this->updatePhysicsSimulation(delta_time);

}

void World::render() {

	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	for (auto&entity : entities) {
		Renderer::render_entity(entity.get(),renderer,nullptr,false);
	}

	this->renderUiComponenets();


	SDL_RenderPresent(renderer);
}

/**
 * @brief Initializes SDL and returns success status
 * @return true if initialization failed, false if successful
 */
bool World::initializeSdl() {
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
void World::initWindowAndRenderer(SDL_Window** window, SDL_Renderer** renderer) {
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
void World::updatePhysicsSimulation(float delta_time) {

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
void World::checkCollisions() {

	for (size_t i = 0; i < entities.size(); ++i) {
		for (size_t j = i + 1; j < entities.size(); ++j) {

			auto& entity_a = entities[i];
			auto& entity_b = entities[j];

			Vector2D collision_normal = is_colliding( entity_a.get(), entity_b.get() );

			if ( collision_normal.x != 0 || collision_normal.y != 0   ) {

				handle_collision(entity_a.get(), entity_b.get(),collision_normal);

				currently_colliding_entities.insert(this->generatePairing(entity_a->entity_id , entity_b->entity_id));
				continue;
			}


			handleCollisionExit(entity_a,entity_b);

		}
	}

}

uint64_t World:: generatePairing (uint32_t first_id ,  uint32_t second_id) {
	return (uint64_t)std::min(first_id,second_id) << 32 | std::max(first_id,second_id);
}

void World::handleCollisionExit(unique_ptr<Entity>& entity_a , unique_ptr<Entity>& entity_b ) {

	uint64_t paired_id = this->generatePairing(entity_a->entity_id , entity_b->entity_id);

	if (prev_colliding_entities.contains(paired_id)) {
		((Rigid_Body*)entity_a->physics.get())->set_affected_by_gravity(true);
		((Rigid_Body*)entity_b->physics.get())->set_affected_by_gravity(true);
	}
}

void World::handleUiEvents(SDL_Event& event) {

	this->ui_manager->handleEvents(event);

}

void World::initialiseUiManager() {

	this->ui_manager = make_unique<UiManager>(&this->window , &this->renderer);

	// create basic component

	this->ui_manager->init();

}

void World::renderUiComponenets() {

	for (auto& component : this->ui_manager->ui_components) {
		if (PopupComponent* comp = dynamic_cast<PopupComponent*>(component.get())) {
			SDL_SetRenderDrawColor(comp->renderer , comp->color.r , comp->color.g , comp->color.b , comp->color.a );
			SDL_RenderClear(comp->renderer);
			SDL_RenderPresent(comp->renderer);
		}
	}

}










