//
// Created by AJYDAN on 25/08/2025.
//

#include "ui_component.h"
#include "ui/ui_action.h"

Vector2D UiComponent::getPosition() {
	return this->position;
}

void UiComponent::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}


