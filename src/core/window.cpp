// Window.cpp
#include "window.h"

#include "rendering/renderer.h"

Window::Window() {
	this->initWindowAndRenderer();
}

Window::~Window() { destroy(); }

void Window::moveFrom(Window&& other) noexcept {
    window_   = other.window_;   other.window_   = nullptr;
    renderer_ = other.renderer_; other.renderer_ = nullptr;
}

bool Window::create(const char* title, int width, int height,Uint32 windowFlags,const char* rendererDriver,int placeOnDisplayIndex) {
    destroy();

    window_ = SDL_CreateWindow(title, width, height, windowFlags);
    if (!window_) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    if (placeOnDisplayIndex >= 0) {
        SDL_Rect b{};
        if (SDL_GetDisplayBounds(placeOnDisplayIndex, &b) == 0) {
            SDL_SetWindowPosition(window_, b.x, b.y);
        }
    }

    renderer_ = SDL_CreateRenderer(window_, rendererDriver);
    if (!renderer_) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        destroy();
        return false;
    }

    return true;
}

void Window::destroy() {

    if (renderer_) {
	    SDL_DestroyRenderer(renderer_);
    	renderer_ = nullptr;
    }

    if (window_) {
	    SDL_DestroyWindow(window_);
    	window_   = nullptr;
    }
}

void Window::setVSync(int vsync ) const {
    if (renderer_) SDL_SetRenderVSync(renderer_, vsync);
}

void Window::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    if (renderer_) SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Window::clear() const {
    if (renderer_) SDL_RenderClear(renderer_);
}

void Window::present() const {
    if (renderer_) SDL_RenderPresent(renderer_);
}

void Window::setPosition(int x, int y) const {
    if (window_) SDL_SetWindowPosition(window_, x, y);
}

void Window::centerOnDisplay(int displayIndex) const {
    if (!window_) return;
    SDL_Rect b{};
    if (SDL_GetDisplayBounds(displayIndex, &b) == 0) {
        SDL_SetWindowPosition(window_, b.x + (b.w/2), b.y + (b.h/2));
    }
}

int Window::id() const {
    return window_ ? SDL_GetWindowID(window_) : 0;
}

void Window::initWindowAndRenderer() {
	SDL_Rect bounds;
	SDL_GetDisplayBounds(2, &bounds);

	this->window_ = SDL_CreateWindow("Physics Engine", 1920, 1080, 0);
	SDL_SetWindowPosition(this->window_, bounds.x, bounds.y);
	this->renderer_ = SDL_CreateRenderer(this->window_, "opengl");
	SDL_SetRenderVSync(this->renderer_, SDL_RENDERER_VSYNC_ADAPTIVE);
}

void Window::render(const vector<unique_ptr<Entity>>& entities) const{

	this->setDrawColor(30, 30, 30, 255);
	this->clear();

	for (auto&entity : entities) {
		Renderer::render_entity(entity.get(),this->renderer_,nullptr,false);
	}

	this->present();
}
