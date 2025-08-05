
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <tuple>
#include <algorithm>

#include "collision/collision.h"
#include "core/entity.h"
#include "physics/physics.h"
#include "physics/physics_component.h"
#include "rendering/renderer.h"
#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "physics/rigid_body.h"

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
 * @brief Initializes SDL and returns success status
 * @return true if initialization failed, false if successful
 */
bool initialize_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        return true;
    } else {
        SDL_Log("SDL Failed To initialize %s", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }
}

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
 * @brief Updates physics for an array of entities
 * @param entities Array of entities to update
 * @param delta_time Time elapsed since last frame
 */
void update_physics_simulation(Entity_List& entities, float delta_time) {

    for (auto &entity : entities) {
    	if (!entity || !entity->physics) {
    		return;
    	}

    	// Each physics component handles its own update logic
    	entity->physics->update(delta_time, entity->shape->get_area_normalised(PPM));

    }
}

/**
 * @brief Initializes the SDL window and renderer
 * @param window Pointer to SDL_Window* to be initialized
 * @param renderer Pointer to SDL_Renderer* to be initialized
 */
void init_window_and_renderer(SDL_Window** window, SDL_Renderer** renderer) {
    SDL_Rect bounds;
    SDL_GetDisplayBounds(2, &bounds);

    *window = SDL_CreateWindow("Physics Engine", 1920, 1080, 0);
    SDL_SetWindowPosition(*window, bounds.x, bounds.y);
    *renderer = SDL_CreateRenderer(*window, "opengl");
    SDL_SetRenderVSync(*renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
}

/**
 * @brief Creates an array of circle entities with random positions and mass
 * @param entities Array to fill with entities
 * @param count Number of entities to create
 */
void create_circle_entities(Entity_List& entities, int count) {
    for (int i = 0; i < count; i++) {
        int radius = 11; // value in m
        float x = rand() % (1920 - 2 * radius) + radius;
        float y = 0 + radius;
        SDL_Color color = RED;
        float mass = 150.0f ; // value in kg

        // Create shape
        auto shape = make_unique<Circle>(radius);

        // Create physics component with gravity disabled
        auto physics = make_unique<Rigid_Body>(mass, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f}, false, true);

        // Set initial position
        physics->set_position(Vector2D{x, y});

        // Create entity using constructor
        entities.push_back(move(make_unique<Entity>(entity_id,move(shape), move(physics), color)));
    		entity_id++;
        entities[i]->collision_type = CIRCLE_COLLISION;
    }
}


/**
 * @brief Checks for collisions between entities
 * @param entities Array of entities to check
 * @param count Number of entities
 * @param delta_time Time elapsed since last frame
 */
void check_collisions(Entity_List& entities, float delta_timem,vector<Colliding_Entities>& currently_colliding_entities, vector<Colliding_Entities> &prev_colliding_entities ) {

    for (auto &entity_a : entities) {
    	for (auto &entity_b : entities) {

    		if (entity_a == entity_b) {
    			continue;
    		}

    		if (is_colliding(entity_a.get(), entity_b.get())) {
     			handle_collision(entity_a.get(), entity_b.get());
    			Colliding_Entities entry(entity_a.get(),entity_b.get());
    			currently_colliding_entities.push_back(entry);
					continue;
    		}


    		Colliding_Entities test(entity_a.get(),entity_b.get());

    		auto iterator = find_if(prev_colliding_entities.begin(), prev_colliding_entities.end(),[&test](Colliding_Entities& entry){
					bool first_is_same = std::get<0>(entry) == std::get<0>(test);
					bool second_is_same = std::get<1>(entry) == std::get<1>(test);

    			return first_is_same && second_is_same;
    		});

    		if (iterator != prev_colliding_entities.end()) {
    			((Rigid_Body*)entity_a->physics.get())->set_affected_by_gravity(true);
    			((Rigid_Body*)entity_b->physics.get())->set_affected_by_gravity(true);
    		}


    	}
    }
}

/**
 * @brief Runs the main application loop
 * @param entities Array of entities
 * @param count Number of entities
 * @param renderer SDL renderer
 */
void run_main_loop(Entity_List& entities, SDL_Renderer* renderer, vector<Colliding_Entities>& currently_colliding_entities, vector<Colliding_Entities> &prev_colliding_entities ) {

	// for (auto &entity_a : entities) {
	// 	dynamic_cast<Rigid_Body*>(entity_a->physics.get())->set_affected_by_gravity(true);
	// }



    bool running = true;
    SDL_Event e;
    uint64_t last_time = SDL_GetPerformanceCounter();

    // Create floor using Entity constructor
    float width = 100;
    float x = 0;
    float y = 1080 - width;
    
    auto floor_shape = make_unique<Rectangle>(1920, width, true);
    auto floor_physics = make_unique<Rigid_Body>(1.0f, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f},true, false);
    floor_physics->set_position(Vector2D{x, y});
    
    unique_ptr<Entity> floor = make_unique<Entity>(entity_id,move(floor_shape), move(floor_physics), GREEN);
		entity_id++;
    floor->collision_type = AABB_COLLISION;
    
    entities.push_back(move(floor));

    while (running) {
        uint64_t current_time = SDL_GetPerformanceCounter();
        float delta_time = (float)(current_time - last_time) / (float)SDL_GetPerformanceFrequency();
        last_time = current_time;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

    		if (!currently_colliding_entities.empty()) {
    			prev_colliding_entities  = currently_colliding_entities;
    			currently_colliding_entities.clear();
    		}

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        update_physics_simulation(entities, delta_time);
        check_collisions(entities, delta_time,currently_colliding_entities,prev_colliding_entities);

        SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
        render_entities(entities, renderer);

        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char** argv) {
    initialize_collision_system();
		Renderer::initialize_render_system();
    initialize_sdl();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    init_window_and_renderer(&window, &renderer);

    int count = 2;
		Entity_List entities;
		vector<Colliding_Entities> currently_colliding_entities;
		vector<Colliding_Entities> prev_colliding_entities;
    create_circle_entities(entities, count);

    run_main_loop(entities, renderer ,currently_colliding_entities,prev_colliding_entities);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}