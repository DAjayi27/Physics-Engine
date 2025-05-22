
#include <math.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include "collision/collision.h"
#include "physics/physics_component.h"
#include "physics/rigid_body.h"
#include "rendering/rectangle.h"
#include "rendering/shape.h"

#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}



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


void handle_input(Shape* moving_box) {
  const bool* keystate = SDL_GetKeyboardState(NULL);
  float speed = 1.0f;
  if (keystate[SDL_SCANCODE_LEFT])  moving_box->circle.position.x -= speed;
  if (keystate[SDL_SCANCODE_RIGHT]) moving_box->circle.position.x += speed;
  if (keystate[SDL_SCANCODE_UP])    moving_box->circle.position.y -= speed;
  if (keystate[SDL_SCANCODE_DOWN])  moving_box->circle.position.y += speed;
}

int main(int argc , char** argv){



  initialise_dispatch();

  initialize_sdl();

  SDL_Window* window ;
  SDL_Renderer *  renderer;

  SDL_CreateWindowAndRenderer("Physics Engine",0,0,SDL_WINDOW_FULLSCREEN,&window,&renderer);
  SDL_SetRenderVSync(renderer,SDL_RENDERER_VSYNC_ADAPTIVE);


    Shape moving_box = create_circle(200,250,100,GREEN,true);
  Shape moving_box2 = create_circle(400,250,100,RED,true);
  Rigid_Body body = {
    .velocity = {0, 0},
    .acceleration = {0, 0},  // if you want persistent acceleration
    .mass = 50.0f,
  };
  Rigid_Body body2 = {
    .velocity = {0, 0},
    .acceleration = {0, 0},  // if you want persistent acceleration
    .mass = 10.0f,
  };

  Physics_Component comp = {.type = PHYSICS_RIGID_BODY , .rigid_body = body };
  Physics_Component comp2 = {.type = PHYSICS_RIGID_BODY , .rigid_body = body2 };

  Entity entity = {&moving_box, &comp};
  Entity entity2 = {&moving_box2, &comp2};

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

    // handle_input(&moving_box);

    // bool collided = is_colliding(&moving_box, &static_box);

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);  // Dark background
    SDL_RenderClear(renderer);

    update_gravity_physics(&entity,deltaTime);
    // update_gravity_physics(&entity2,deltaTime);

    SDL_SetRenderDrawColor(renderer,RED.r,RED.g,RED.b,RED.a);
    render_circle_bresenham(entity.shape,renderer,true);
    render_circle_bresenham(entity2.shape,renderer,true);


    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();




  return 0;
}
