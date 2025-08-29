// Window.h
#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include <string>
#include <utility>
#include <vector>

#include "entity.h"

using std::vector;
using std::unique_ptr;

class Window {
public:
	Window();
	~Window();

	// Create / destroy
	bool create(const char* title, int width, int height,Uint32 windowFlags = 0,const char* rendererDriver = "opengl",int placeOnDisplayIndex = -1); // -1 = don't reposition
	void initWindowAndRenderer();
	void destroy();

	// Accessors
	[[nodiscard]] SDL_Window*   sdlWindow()   const { return window_; }
	[[nodiscard]] SDL_Renderer* sdlRenderer() const { return renderer_; }
	SDL_Window**   sdl_window_ptr()   { return &window_; }
	SDL_Renderer** sdl_renderer_ptr() { return &renderer_; }
	explicit operator bool() const    { return window_ && renderer_; }

	// Convenience
	void setVSync(int vsync = SDL_RENDERER_VSYNC_ADAPTIVE) const;
	void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;
	void clear()   const;
	void present() const;
	void render(const vector<unique_ptr<Entity>>& entities) const;

	// Window helpers
	void setPosition(int x, int y) const;
	void centerOnDisplay(int displayIndex) const;
	int  id() const; // SDL_GetWindowID

private:
	void moveFrom(Window&& other) noexcept;

	SDL_Window*   window_   = nullptr;
	SDL_Renderer* renderer_ = nullptr;
};
