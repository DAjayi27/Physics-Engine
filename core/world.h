// World.h
#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "entity.h"
#include <SDL3/SDL.h>
#include <set>
#include <cmath>
// #include <SDL3_image/SDL_image.h>


using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::set;
using Entity_List  = vector<unique_ptr<Entity>>;
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
	void handleUiEvents(SDL_Event& event);

private:

	vector<unique_ptr<Entity>> entities;
	set<uint64_t> currently_colliding_entities;
	set<uint64_t> prev_colliding_entities;

	float gravity = 9.8f; // or use a vector for 2D gravity
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int PPM = 50;
	uint64_t last_time = SDL_GetPerformanceCounter();


	bool initializeSdl();
	void initWindowAndRenderer(SDL_Window** window, SDL_Renderer** renderer);
	void updatePhysicsSimulation(float delta_time);
	void checkCollisions();
	uint64_t generatePairing (uint32_t first_id ,  uint32_t second_id);
	void handleCollisionExit(unique_ptr<Entity>& entity_a , unique_ptr<Entity>& entity_b );
};
