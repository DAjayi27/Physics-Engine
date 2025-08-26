//
// Created by AJYDAN on 25/08/2025.
//

#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include <memory>
#include <vector>
#include "ui/ui_component.h"

using std::vector;
using std::unique_ptr;


class ui_manager {

public:
	vector<unique_ptr<UiComponent>> ui_components ;

	void handleEvent()

};



#endif //UI_MANAGER_H
