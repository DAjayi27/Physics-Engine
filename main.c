
#include <math.h>
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

#include "rendering/rectangle.h"

#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}


typedef struct {
  float x, y, w, h;
} AABB;

bool aabb_collision(Rectangle* a, Rectangle* b) {
  return (a->position.x < b->position.x + b->width &&
          a->position.x + a->width > b->position.x &&
          a->position.y < b->position.y + b->height &&
          a->position.y + a->height > b->position.y);
}


void render_circle_bresenham(SDL_Renderer *renderer, int cx, int cy, int radius,bool is_fill) {
  int x = radius;
  int y = 0;
  int d = 3 - 2 * radius;

  while (x >= y) {
    SDL_RenderPoint(renderer, cx + x, cy + y);
    SDL_RenderPoint(renderer, cx - x, cy + y);
    SDL_RenderPoint(renderer, cx + x, cy - y);
    SDL_RenderPoint(renderer, cx - x, cy - y);
    SDL_RenderPoint(renderer, cx + y, cy + x);
    SDL_RenderPoint(renderer, cx - y, cy + x);
    SDL_RenderPoint(renderer, cx + y, cy - x);
    SDL_RenderPoint(renderer, cx - y, cy - x);

    if (is_fill) {

      SDL_RenderLine(renderer,cx + x,cy + y,cx - x,cy + y);
      SDL_RenderLine(renderer,cx + x,cy - y,cx - x,cy - y);
      SDL_RenderLine(renderer,cx + y,cy + x,cx - y,cy + x);
      SDL_RenderLine(renderer,cx + y,cy - x,cx - y,cy - x);

    }

    if (d < 0) {
      d = d + (2 * (3 + 2*y) );
    } else {
      d = d + (2 * (5 - 2*x + 2*y));
      x--;
    }
    y++;


  }
}


void render_circle_mid_point(SDL_Renderer *renderer, int cx, int cy, int radius) {
  int x = 0;
  int y = -radius;
  int d = -radius + 0.25;

  while (x < -y) {

    if (d > 0) {
      y++;
      d = d + (2 * (x + y) + 1 );
    } else {
      d = d + 2 * x + 1;

    }

    SDL_RenderPoint(renderer, cx + x, cy + y);
    SDL_RenderPoint(renderer, cx - x, cy + y);
    SDL_RenderPoint(renderer, cx + x, cy - y);
    SDL_RenderPoint(renderer, cx - x, cy - y);
    SDL_RenderPoint(renderer, cx + y, cy + x);
    SDL_RenderPoint(renderer, cx - y, cy + x);
    SDL_RenderPoint(renderer, cx + y, cy - x);
    SDL_RenderPoint(renderer, cx - y, cy - x);




    x++;
  }
}


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






int main(int argc , char** argv){

  initialize_sdl();

  SDL_Window* window ;
  SDL_Renderer *  renderer;

  SDL_CreateWindowAndRenderer("Physics Engine",1000,1000,0,&window,&renderer);

  AABB staticBox = {300, 250, 100, 100};   // Stationary rectangle


  Rectangle* moving_box = new_rectangle(AABB_COLLISION,300,250,100,100,RED);
  Rectangle* static_box = new_rectangle(AABB_COLLISION,100,100,100,100,WHITE);
  bool running = true;
  SDL_Event e;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    const bool* keystate = SDL_GetKeyboardState(NULL);
    float speed = 5.0f;
    if (keystate[SDL_SCANCODE_LEFT])  moving_box->position.x -= speed;
    if (keystate[SDL_SCANCODE_RIGHT]) moving_box->position.x += speed;
    if (keystate[SDL_SCANCODE_UP])    moving_box->position.y -= speed;
    if (keystate[SDL_SCANCODE_DOWN])  moving_box->position.y += speed;

    bool collided = aabb_collision(moving_box, static_box);

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);  // Dark background
    SDL_RenderClear(renderer);

    // Draw static box in white
    render_rect(static_box,renderer,NULL);

    // Draw moving box - red if colliding, green otherwise
    if (collided) {
      moving_box->color = RED;  // Red
    } else {
      moving_box->color = GREEN;  // Green
    }
    render_rect(moving_box,renderer,NULL);

    render_circle_mid_point(renderer,500,500,400);
    SDL_SetRenderDrawColor(renderer,RED.r,RED.g,RED.b,RED.a);
    render_circle_bresenham(renderer,500,500,400,false);


    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();




  return 0;
}