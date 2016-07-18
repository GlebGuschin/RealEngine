#pragma once

#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Referenced.hpp"

struct GamepadState {
	int t;
};


class InputListener : public Listener {

	virtual void onMouseAction(const MouseState&) = 0;
	virtual void onKeyboardAction(const KeyboardState&) = 0;
	virtual void onGamepadAction(const GamepadState&) = 0;

};


class Sensor : public Referenced {

public:
	
};




#endif