//
// Created by AJYDAN on 25/08/2025.
//

#include "ui_manager.h"

#include <algorithm>

#include "components/ui_main.h"
#include "components/ui_popup.h"
#define GREEN (SDL_Color){0, 255, 0, 255}
#define RED (SDL_Color){255, 0, 0, 255}
#define WHITE (SDL_Color){255, 255, 255, 255}


UiManager::UiManager(SDL_Window** parent_window, SDL_Renderer** parent_renderer) {

	this->parent_renderer = parent_renderer;
	this->parent_window = parent_window;
}

void UiManager::init() {

	//create a main component
	unique_ptr<UiMainComponent> main = make_unique<UiMainComponent>(10.0f,10.0f,SDL_Color{10,10,10,1});

	this->ui_components.push_back(move(main));

}


void UiManager::handleUiActions() {
	UIAction uiAction;
	while (!pending_ui_actions.empty()){

		uiAction = pending_ui_actions.front(); // get the last element

		pending_ui_actions.pop(); // remove it


		if (uiAction.actionType == UIActionType::CreatePopup) {
			auto component = make_unique<PopupComponent>(this->parent_window ,this->parent_renderer,RED,uiAction.position);
			this->ui_components.push_back(move(component));
			printf("Popup Added\n");
		}
		else if (uiAction.actionType == UIActionType::CloseAllPopup) {

			ui_components.erase(
				std::remove_if(ui_components.begin() , ui_components.end(),  [uiAction](unique_ptr<UiComponent>& component) {
					return std::type_index(typeid(*component)) == uiAction.type;
				}),
				ui_components.end()
			);

			printf("Popup Removed\n");

		}
	}

}

void UiManager::handleEvents(SDL_Event& e) {

	for (auto& component  : ui_components) {
		vector<UIAction> actions =  component->handleEvent(e);

		for (auto& action : actions) {
			pending_ui_actions.push(action);
		}
	}

	this->handleUiActions();

}

