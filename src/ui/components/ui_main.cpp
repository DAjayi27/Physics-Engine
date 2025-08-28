//
// Created by AJYDAN on 26/08/2025.
//

#include "ui_main.h"

#include "ui_popup.h"
#include "ui/ui_action.h"

UiMainComponent::UiMainComponent(float x, float y, SDL_Color color) {
	this->setPosition(x,y);
	this->color = color;
}


vector<UIAction> UiMainComponent::handleEvent(SDL_Event& event) {

	vector<UIAction> actions;

	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == 3) {


		actions.push_back(UIAction{
		UIActionType::CloseAllPopup,
		{event.button.x, event.button.y},
		nullptr,
		typeid(PopupComponent)
		});


		actions.push_back(UIAction{
		UIActionType::CreatePopup,
		{event.button.x, event.button.y},
		nullptr,
			typeid(PopupComponent)
		});
	}
	else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == 1) {
		actions.push_back(UIAction{
		UIActionType::CloseAllPopup,
		{event.button.x, event.button.y},
		nullptr,
		typeid(PopupComponent)
		});
	}

	return actions;


}

