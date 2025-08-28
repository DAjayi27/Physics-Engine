//
// Created by AJYDAN on 25/08/2025.
//

#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H
#include <vector>
#include <SDL3/SDL_events.h>

#include "core/vector.h"

struct UIAction;

using std::vector;

class UiComponent {
public:
	virtual ~UiComponent() = default;
	virtual vector<UIAction> handleEvent(SDL_Event& e) = 0;
	void setPosition(float x, float y);
	Vector2D getPosition();
private:
	Vector2D position = {0,0};

};



#endif //UI_ELEMENT_H
