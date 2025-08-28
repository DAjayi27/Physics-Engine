//
// Created by AJYDAN on 26/08/2025.
//

#ifndef UI_ACTION_H
#define UI_ACTION_H
#include "core/vector.h"


#include <cstdint>
#include <memory>
#include <string>
#include <typeindex>

class UiComponent;

enum class UIActionType  {
	NONE,
	OPEN,
	CLOSE,
	CreatePopup,
	ClosePopup,
	CloseAllPopup
};

/**
 *The idea here is that you have a action type, the position the action takes place,
 *and which component you want the action tho happen to
 *
 */
struct UIAction {
	UIActionType actionType = UIActionType::NONE;
	Vector2D position = {0,0};
	UiComponent* component = nullptr; // optional
	std::type_index type = typeid(void);
} ;



#endif //UI_ACTION_H
