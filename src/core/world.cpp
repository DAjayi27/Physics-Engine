#include "world.h"

#include "collision/collision.h"
#include "physics/rigid_body.h"
#include "rendering/renderer.h"
#include <iostream>

#include "ui/components/ui_popup.h"

#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 1}
#define WHITE (SDL_Color){255, 255, 255, 255}

World::World() {

	this->entity_count = 0;
	this->window = nullptr;
	this->ui_manager = nullptr;
	this->physics_system = nullptr;
}

bool World::init() {

	Renderer::initialize_render_system();
	this->collision_manager = make_unique<CollisionManager>();

	if (!initializeSdl()) {
		return false;
	}
	this->window = make_unique<Window>();
	this->physics_system = make_unique<PhysicsSystem>();
	this->initialiseUiManager();

	return true;
}

bool World::quit() {
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


	this->collision_manager->checkCollisions(entities);
	this->physics_system->update(entities , 0.016 , getPPM());

}

void World::render() {

	this->window->render(this->entities);

	// this->renderUiComponenets();

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


void World::handleUiEvents(SDL_Event& event) {

	this->ui_manager->handleEvents(event);

}

void World::initialiseUiManager() {

	this->ui_manager = make_unique<UiManager>(this->window->sdl_window_ptr(),this->window->sdl_renderer_ptr());

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

float World::getPPM() {
	return this->PPM;
}











