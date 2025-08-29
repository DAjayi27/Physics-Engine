// #define SDL_MAIN_HANDLED
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
// #include <SDL3_image/SDL_image.h>
#include <vector>
#include <tuple>
#include <algorithm>

#include "collision/collision.h"
#include "core/entity.h"
#include "core/world.h"
#include "physics/physics.h"
#include "physics/physics_component.h"
#include "rendering/renderer.h"
#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "physics/rigid_body.h"
#include <iostream>
#include <random>


// Selective using declarations to reduce std:: prefixes
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::tuple;
using Entity_List  = vector<unique_ptr<Entity>>;
using Colliding_Entities = tuple<Entity*,Entity*>;
using std::find_if;


// Color definitions
#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}


//
int entity_id = 0;

const int PPM = 50; // 5 PX = 1M




/**
 * @brief Handles user input to move an entity
 * @param entity Pointer to the entity to move
 */
void handle_input(Entity* entity) {
    const bool* keystate = SDL_GetKeyboardState(NULL);
    float speed = 1.0f;

    if (keystate[SDL_SCANCODE_LEFT])  entity->set_position_x(entity->get_position().x - speed);
    if (keystate[SDL_SCANCODE_RIGHT]) entity->set_position_x(entity->get_position().x + speed);
    if (keystate[SDL_SCANCODE_UP])    entity->set_position_y(entity->get_position().y - speed);
    if (keystate[SDL_SCANCODE_DOWN])  entity->set_position_y(entity->get_position().y + speed);
}

/**
 * @brief Renders an array of entities
 * @param entities Array of entities to render
 * @param count Number of entities in the array
 * @param renderer SDL renderer
 */
void render_entities(Entity_List& entities, SDL_Renderer* renderer) {
    for (auto &entity : entities) {
    	Renderer::render_entity(entity.get(), renderer, nullptr, false);
    }
}





/**
 * @brief Creates an array of circle entities with random positions and mass
 * @param entities Array to fill with entities
 * @param count Number of entities to create
 */
vector<unique_ptr<Entity>> create_circle_entities(unique_ptr<World>& world,int count,std::uniform_int_distribution<uint32_t> dist ,std::mt19937_64 gen) {

	Entity_List entities;

  for (int i = 0; i < count; i++) {
      int radius = 11; // value in m
      float x = rand() % (1920 - 2 * radius) + radius;
      float y = 0 + radius;
      SDL_Color color = RED;
      float mass = 1.50f ; // value in kg

      // Create shape
      auto shape = make_unique<Circle>(radius);

  		std::uniform_real_distribution<float> limit(-10, 10);

      // Create physics component with gravity disabled
      auto physics = make_unique<Rigid_Body>(mass, 0.1f, 1.0f, Vector2D{limit(gen), 0.0f}, Vector2D{0.0f, 0.0f}, false, true,world->getPPM());

      // Set initial position
      physics->set_position(Vector2D{x, y});

      // Create entity using constructor
      entities.push_back(move(make_unique<Entity>(dist(gen),move(shape), move(physics), color)));
      entities[i]->collision_type = CIRCLE_COLLISION;
  }

	return move(entities);

}



int main(int argc, char** argv) {

	std::random_device rd;  // Seed source
	std::mt19937_64 gen(rd());  // 64-bit Mersenne Twister
	std::uniform_int_distribution<uint32_t> dist;

	auto world = make_unique<World>();

	world->init();


  int count = 60;
	Entity_List entities = create_circle_entities( world,count, dist,gen);

	world->addEntities(entities);


	float x = 0;
	float y = 1080 ;

	auto floor_shape = make_unique<Rectangle>(1920, 10, true);
	auto floor_physics = make_unique<Rigid_Body>(0, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f},true, false ,world->getPPM());
	floor_physics->set_position(Vector2D{x, y});
	auto floor = make_unique<Entity>(dist(gen),move(floor_shape),move(floor_physics),GREEN);



	auto left_wall_shape = make_unique<Rectangle>(10, 1080, true);
	auto left_wall_physics = make_unique<Rigid_Body>(0, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f},true, false ,world->getPPM());
	left_wall_physics->set_position(Vector2D{0, 0});
	auto left_wall  = make_unique<Entity>(dist(gen),move(left_wall_shape),move(left_wall_physics),GREEN);

	auto right_wall_shape = make_unique<Rectangle>(10, 1080, true);
	auto right_wall_physics = make_unique<Rigid_Body>(0, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f},true, false ,world->getPPM());
	right_wall_physics->set_position(Vector2D{1910, 0});
	auto right_wall  = make_unique<Entity>(dist(gen),move(right_wall_shape),move(right_wall_physics),GREEN);

	world->addEntity(move(floor));
	world->addEntity(move(left_wall));
	world->addEntity(move(right_wall));

	SDL_Event e;

	bool running = true;
	while (running) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				running = false;
			}else {
				world->handleUiEvents(e);
			}
		}


		world->update();  // your physics update
		world->render();  // your render function
	}



  return 0;
}

