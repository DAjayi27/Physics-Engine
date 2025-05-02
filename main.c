
#include <math.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include "collision/collision.h"
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

  SDL_CreateWindowAndRenderer("Physics Engine",1000,1000,0,&window,&renderer);

  Shape moving_box = create_circle(200,250,100,RED,true);
  Shape static_box = create_rect(100,100,100,100,WHITE,true);

  bool running = true;
  SDL_Event e;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    handle_input(&moving_box);

    bool collided = is_colliding(&moving_box, &static_box);

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);  // Dark background
    SDL_RenderClear(renderer);

    // Draw static box in white
    render_rect(&static_box.rect,renderer,NULL);

    // Draw moving box - red if colliding, green otherwise
    if (collided) {
      moving_box.circle.color = RED;  // Red
    } else {
      moving_box.circle.color = GREEN;  // Green
    }
    render_circle_bresenham(&moving_box.circle,renderer,true);


    // // render_circle_mid_point(renderer,500,500,400,true);
    // render_circle_bresenham(renderer,500,500,400,false);


    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();




  return 0;
}
