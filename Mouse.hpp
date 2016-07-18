#pragma once

#ifndef __MOUSE_HPP__
#define __MOUSE_HPP__

#include "InputCommon.hpp"

struct MousePosition {
	int x, y;

	bool operator==(const MousePosition& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

};

enum MOUSE_BUTTON_TYPE {
	MOUSE_BUTTON_LEFT = 0,	
	MOUSE_BUTTON_RIGHT = 2,
	MOUSE_BUTTON_MIDDLE = 1,
	//MOUSE_BUTTON_WHEEL = 4
	MOUSE_BUTTON_MAX
};


struct MouseState {
	
	INPUT_ACTION_TYPE actions[MOUSE_BUTTON_MAX];

	int wheelValue;

	MousePosition newPos, oldPos;
	
	bool isMoving() const { return !(newPos == oldPos); }

	bool isAction() const { 

		for (int i = 0; i < MOUSE_BUTTON_MAX; i++) {
			if (actions[i] != INPUT_ACTION_NONE) return true;
		}

		return false;
	}

	int getWheelValue() const { return(wheelValue); }

	const MousePosition& getNewPosition() const { return(newPos); }
	const MousePosition& getOldPosition() const { return(oldPos); }

	MouseState() {
	
		//actions[MOUSE_BUTTON_MAX];
	}

};


#endif
