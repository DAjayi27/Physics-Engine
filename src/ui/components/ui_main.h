	//
// Created by AJYDAN on 26/08/2025.
//

#ifndef UI_MAIN_H
#define UI_MAIN_H
#include "ui_component.h"


class UiMainComponent : public UiComponent {

public:
	UiMainComponent(float x,float y,SDL_Color);
	SDL_Color color;
	vector<UIAction> handleEvent(SDL_Event& e) override;

};



#endif //UI_MAIN_H
