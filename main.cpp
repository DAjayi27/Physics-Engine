
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include "collision/collision.h"
#include "core/entity.h"
#include "physics/physics.h"
#include "physics/physics_component.h"
#include "rendering/renderer.h"
#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "physics/rigid_body.h"

// Color definitions
#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}

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
void render_entities(Entity* entities, int count, SDL_Renderer* renderer) {
    for (int i = 0; i < count; ++i) {
        Renderer::render_entity(&entities[i], renderer, nullptr, false);
    }
}

/**
 * @brief Updates physics for an array of entities
 * @param entities Array of entities to update
 * @param count Number of entities in the array
 * @param delta_time Time elapsed since last frame
 */
void update_physics_simulation(Entity* entities, int count, float delta_time) {
    for (int i = 0; i < count; ++i) {
        update_physics(&entities[i], delta_time);
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
void create_circle_entities(Entity* entities, int count) {
    for (int i = 0; i < count; i++) {
        int radius = 10;
        float x = rand() % (1920 - 2 * radius) + radius;
        float y = rand() % (1080 - 2 * radius) + radius;
        SDL_Color color = RED;
        float mass = 10.0f + ((float)rand() / RAND_MAX) * (50.0f - 10.0f);
        
        // Create shape
        auto shape = std::make_unique<Circle>(radius);
        
        // Create physics component
        auto physics = std::make_unique<Rigid_Body>(mass, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f},false, true);
        
        // Set initial position
        physics->set_position(Vector2D{x, y});
        
        // Create entity using constructor
        entities[i] = Entity(std::move(shape), std::move(physics), color);
        entities[i].collision_type = CIRCLE_COLLISION;
    }
}

/**
 * @brief Checks for collisions between entities
 * @param entities Array of entities to check
 * @param count Number of entities
 * @param delta_time Time elapsed since last frame
 */
void check_collisions(Entity* entities, int count, float delta_time) {
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            Entity* entity_a = &entities[i];
            Entity* entity_b = &entities[j];

            if (is_colliding(entity_a, entity_b)) {
                SDL_SetLogPriority(SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_INFO);
                SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "Collision detected");
                handle_collision(entity_a, entity_b);
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
void run_main_loop(Entity* entities, int count, SDL_Renderer* renderer) {
    bool running = true;
    SDL_Event e;
    uint64_t last_time = SDL_GetPerformanceCounter();

    // Create floor using Entity constructor
    float width = 100;
    float x = 0;
    float y = 1080 - width;
    
    auto floor_shape = std::make_unique<Rectangle>(1920, width, true);
    auto floor_physics = std::make_unique<Rigid_Body>(1.0f, 0.1f, 0.5f, Vector2D{0.0f, 0.0f}, Vector2D{0.0f, 0.0f},true, false);
    floor_physics->set_position(Vector2D{x, y});
    
    Entity floor(std::move(floor_shape), std::move(floor_physics), GREEN);
    floor.collision_type = AABB_COLLISION;
    
    entities[count - 1] = floor;

    while (running) {
        uint64_t current_time = SDL_GetPerformanceCounter();
        float delta_time = (float)(current_time - last_time) / (float)SDL_GetPerformanceFrequency();
        last_time = current_time;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        update_physics_simulation(entities, count, delta_time);
        check_collisions(entities, count, delta_time);

        SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
        render_entities(entities, count, renderer);

        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char** argv) {
    initialize_collision_system();
    initialize_sdl();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    init_window_and_renderer(&window, &renderer);

    int count = 2;
    Entity entities[count + 1];
    create_circle_entities(entities, count);

    run_main_loop(entities, count, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}