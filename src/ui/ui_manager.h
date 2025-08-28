//
// Created by AJYDAN on 25/08/2025.
//

#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include <memory>
#include <queue>
#include <vector>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include "ui_action.h"
#include "components/ui_component.h"


using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;
using std::queue;


class UiManager {

private:
	SDL_Window ** parent_window = nullptr;
	SDL_Renderer ** parent_renderer = nullptr;
	queue<UIAction> pending_ui_actions;

public:
	UiManager(SDL_Window ** parent_window , SDL_Renderer ** parent_renderer);
	vector<unique_ptr<UiComponent>> ui_components;
	void init();
	void handleEvents(SDL_Event& e);
	void handleUiActions();

};



#endif //UI_MANAGER_H
