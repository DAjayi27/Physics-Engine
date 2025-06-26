
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
#include "physics/rigid_body.h"
#include "rendering/renderer.h"
#include "shapes/shape.h"

#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}
#define null NULL


bool initialize_sdl() {

  if (SDL_Init(SDL_INIT_VIDEO)) {
    return true;
  }
  else {
    SDL_Log("SDL Failed To initalize %s",SDL_GetError());
    SDL_Quit();
    exit(-1);
  }


}


/**
 * @brief Handles user input to move a box entity.
 *
 * This function checks the current state of the keyboard and updates the position
 * of the given entity based on arrow key inputs. The movement speed is fixed at 1.0f.
 *
 * @param moving_box Pointer to the entity whose position will be updated.
 */
void handle_input(Entity* moving_box) {
  const bool* keystate = SDL_GetKeyboardState(NULL);
  float speed = 1.0f;
  if (keystate[SDL_SCANCODE_LEFT])  moving_box->position.x -= speed;
  if (keystate[SDL_SCANCODE_RIGHT]) moving_box->position.x += speed;
  if (keystate[SDL_SCANCODE_UP])    moving_box->position.y -= speed;
  if (keystate[SDL_SCANCODE_DOWN])  moving_box->position.y += speed;
}

/**
 * @brief Renders an array of circle entities using the Bresenham algorithm.
 *
 * This function iterates through an array of entities and renders each circle
 * using the specified SDL renderer. The rendering is performed using the
 * Bresenham algorithm for drawing circles.
 *
 * @param circles Pointer to an array of entities representing circles to render.
 * @param number The number of entities in the array.
 * @param renderer Pointer to the SDL_Renderer used for rendering.
 */
void render_entities(Entity* circles, int number,SDL_Renderer* renderer) {

  for (int i = 0; i < number; ++i) {
    render_entity(&circles[i],renderer,null,false);
  }


}

/**
 * @brief Updates the physics of an array of entities.
 *
 * This function iterates through an array of entities and updates their physics
 * properties based on gravity and the elapsed time.
 *
 * @param circles Pointer to an array of entities to update.
 * @param number The number of entities in the array.
 * @param dt The time delta used for physics calculations.
 */
void update_physics(Entity* circles, int number,float dt) {
  for (int i = 0; i < number; ++i) {
    update_gravity_physics(&circles[i],dt);
  }
}


/**
 * @brief Initializes the SDL window and renderer.
 * @param window Pointer to SDL_Window* to be initialized.
 * @param renderer Pointer to SDL_Renderer* to be initialized.
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
 * @brief Creates an array of circle entities with random positions and mass.
 * @param entities Array to fill with entities.
 * @param count Number of entities to create.
 */
void create_circle_entities(Entity* entities, int count) {
    for (int i = 0; i < count; i++) {
        int radius = 10;
        float x = rand() % (1920 - 2 * radius) + radius;
        float y = rand() % (1080 - 2 * radius) + radius;
        SDL_Color color = RED;
        Physics_Type physics = PHYSICS_RIGID_BODY;
        float mass = 10.0f + ((float)rand() / RAND_MAX) * (50.0f - 10.0f);
        entities[i] = create_circle_zero_entity(x, y, radius, color, physics, mass);
    }
}

/**
 * @brief Runs the main application loop.
 * @param entities Array of entities.
 * @param count Number of entities.
 * @param renderer SDL renderer.
 */
void run_main_loop(Entity* entities, int count, SDL_Renderer* renderer) {
    bool running = true;
    SDL_Event e;
    uint64_t lastTime = SDL_GetPerformanceCounter();

    while (running) {
        uint64_t currentTime = SDL_GetPerformanceCounter();
        float deltaTime = (float)(currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = currentTime;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        float width = 100;
        float x =  0;
        float y = 1080-width;


        Entity floor =  create_rect_entity(x,y,1920,width,true,GREEN);
        render_entity(&floor,renderer,null,true);


        update_physics(entities, count, deltaTime);

        SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);
        render_entities(entities, count, renderer);

        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char** argv) {
    initialise_render_dispatch();
    initialise_collision_dispatch();
    initialize_sdl();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    init_window_and_renderer(&window, &renderer);

    int count = 10;
    Entity entities[count];
    create_circle_entities(entities, count);



    run_main_loop(entities, count, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}