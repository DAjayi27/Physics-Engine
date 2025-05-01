
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>

typedef struct {
  float x, y, w, h;
} AABB;

bool aabb_collision(AABB a, AABB b) {
  return (a.x < b.x + b.w &&
          a.x + a.w > b.x &&
          a.y < b.y + b.h &&
          a.y + a.h > b.y);
}

int main(int argc , char** argv){

  SDL_Window* window ;
  SDL_Renderer *  renderer;

  SDL_Init(SDL_INIT_VIDEO);

 SDL_CreateWindowAndRenderer("Physics Engine",1000,1000,0,&window,&renderer);

  AABB staticBox = {300, 250, 100, 100};   // Stationary rectangle
  AABB movingBox = {100, 100, 100, 100};   // Controlled with keys

  bool running = true;
  SDL_Event e;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    float speed = 5.0f;
    if (keystate[SDL_SCANCODE_LEFT])  movingBox.x -= speed;
    if (keystate[SDL_SCANCODE_RIGHT]) movingBox.x += speed;
    if (keystate[SDL_SCANCODE_UP])    movingBox.y -= speed;
    if (keystate[SDL_SCANCODE_DOWN])  movingBox.y += speed;

    bool collided = aabb_collision(movingBox, staticBox);

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);  // Dark background
    SDL_RenderClear(renderer);

    // Draw static box in white
    SDL_FRect rect1 = {staticBox.x, staticBox.y, staticBox.w, staticBox.h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect1);

    // Draw moving box - red if colliding, green otherwise
    SDL_FRect rect2 = {movingBox.x, movingBox.y, movingBox.w, movingBox.h};
    if (collided) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green
    }
    SDL_RenderFillRect(renderer, &rect2);

    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();




  return 0;
}