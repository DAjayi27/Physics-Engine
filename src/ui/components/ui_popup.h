//
// Created by AJYDAN on 25/08/2025.
//

#ifndef POPUP_H
#define POPUP_H

#include <SDL3/SDL_render.h>

#include "ui_component.h"

class PopupComponent : public UiComponent  {



public:
	PopupComponent(SDL_Window** parent_window , SDL_Renderer** parent_renderer , SDL_Color color,Vector2D position);
	~PopupComponent() override;
	SDL_Color color;
	vector<UIAction> handleEvent(SDL_Event& e) override;
	SDL_Window* window;
	SDL_Renderer* renderer;

};



#endif //POPUP_H
