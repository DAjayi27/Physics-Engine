//
// Created by AJYDAN on 25/08/2025.
//

#include "ui_popup.h"

#include <iostream>
#include <SDL3/SDL_render.h>

#include "../ui_action.h"

// Color definitions
#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}

PopupComponent::PopupComponent(SDL_Window** parent_window, SDL_Renderer** parent_renderer, SDL_Color color,Vector2D position) {

	this->window = SDL_CreatePopupWindow(*parent_window, position.x , position.y ,100,100 , SDL_WINDOW_POPUP_MENU);
	this->renderer = SDL_CreateRenderer(this->window,"");
	this->color = color;

	SDL_SetRenderDrawColor(this->renderer,RED.r,RED.g,RED.b,RED.a);
	SDL_RenderClear(this->renderer);
}



vector<UIAction> PopupComponent::handleEvent(SDL_Event& event) {

	vector<UIAction> test;

	return test;

}

PopupComponent::~PopupComponent() {

	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);

}

