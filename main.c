
#include <math.h>
#include <stdio.h>
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


void handle_input(Entity* moving_box) {
  const bool* keystate = SDL_GetKeyboardState(NULL);
  float speed = 1.0f;
  if (keystate[SDL_SCANCODE_LEFT])  moving_box->position.x -= speed;
  if (keystate[SDL_SCANCODE_RIGHT]) moving_box->position.x += speed;
  if (keystate[SDL_SCANCODE_UP])    moving_box->position.y -= speed;
  if (keystate[SDL_SCANCODE_DOWN])  moving_box->position.y += speed;
}

int main(int argc , char** argv){



  initialise_dispatch();

  initialize_sdl();

  SDL_Window* window ;
  SDL_Renderer *  renderer;

  SDL_CreateWindowAndRenderer("Physics Engine",800,800,0,&window,&renderer);
  SDL_SetRenderVSync(renderer,SDL_RENDERER_VSYNC_ADAPTIVE);


  Entity entity = create_circle_physics_entity(10,10,100,RED,PHYSICS_RIGID_BODY,{.x = 0,.y = 0},{.x = 0,.y = 0},10);
  Entity entity2 = create_circle_physics_entity(10,10,100,RED,PHYSICS_RIGID_BODY,{.x = 0,.y = 0},{.x = 0,.y = 0},50);

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
    render_circle_bresenham(&entity,renderer,true);
    // render_circle_bresenham(entity2.shape,renderer,true);


    SDL_RenderPresent(renderer);

  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();




  return 0;
}
