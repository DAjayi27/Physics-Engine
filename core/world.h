// World.h
#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "entity.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::tuple;
using std::tuple;
using Entity_List  = vector<unique_ptr<Entity>>;
using Colliding_Entities = tuple<Entity*,Entity*>;
using std::find_if;

class World {
public:

	int entity_count = 0;

	World();
	bool init();
	bool quit();
	void addEntity(unique_ptr<Entity> entity);
	void addEntities(vector<unique_ptr<Entity>>& entities);
	void update();
	void render();

private:

	vector<unique_ptr<Entity>> entities;
	vector<Colliding_Entities> currently_colliding_entities;
	vector<Colliding_Entities> prev_colliding_entities;
	float gravity = 9.8f; // or use a vector for 2D gravity
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int PPM = 50;
	uint64_t last_time = SDL_GetPerformanceCounter();


	bool initialize_sdl();
	void init_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer);
	void update_physics_simulation(float delta_time);
	void check_collisions(float delta_time );
};
