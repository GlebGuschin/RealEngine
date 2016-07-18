#pragma once

#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#include "InputCommon.hpp"
#include "windows.h"


enum KEYBOARD_MODIFICATOR_TYPE {
	KEYBOARD_MODIFICATOR_CTRL = 1,
	KEYBOARD_MODIFICATOR_SHIFT = 2,
	KEYBOARD_MODIFICATOR_ALT = 4	
};

struct KeyboardState {

	unsigned modificators;
	
	unsigned key;


	KeyboardState() {

		//bCTRL = bSHIFT = bALT = true;

	}

};


#if 1
enum KEY_TYPE {

	KEY_NONE = 0x00,
	KEY_ESCAPE = VK_ESCAPE,
	KEY_ENTER = VK_RETURN,

	KEY_TAB = VK_TAB,
	KEY_INSERT = VK_INSERT,
	KEY_BACKSPACE = VK_BACK,
	KEY_SPACE = VK_SPACE,

	KEY_PREV = VK_PRIOR,
	KEY_NEXT = VK_NEXT,

	KEY_UP = VK_UP,
	KEY_DOWN = VK_DOWN,

	KEY_TILDA = 96,


	KEY_0 = '0',
	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',
	KEY_5 = '5',
	KEY_6 = '6',
	KEY_7 = '7',
	KEY_8 = '8',
	KEY_9 = '9',


	KEY_A = 'A',
	KEY_B = 'B',
	KEY_C = 'C',
	KEY_E = 'E',
	KEY_F = 'F',
	KEY_D = 'D',
	KEY_H = 'H',
	KEY_G = 'G',
	KEY_I = 'I',
	KEY_J = 'J',
	KEY_K = 'K',
	KEY_L = 'L',
	KEY_N = 'N',
	KEY_M = 'M',
	KEY_P = 'P',
	KEY_O = 'O',
	KEY_S = 'S',
	KEY_T = 'T',
	KEY_R = 'R',
	KEY_Q = 'Q',
	KEY_V = 'V',
	KEY_U = 'U',
	KEY_W = 'W',
	KEY_Y = 'Y',
	KEY_Z = 'Z',


	/*
	KEY_SEMICOLON	= 0x27,
	KEY_APOSTROPHE	= 0x28,
	KEY_GRAVE		= 0x29,
	KEY_LSHIFT		= 0x2A,
	KEY_BACKSLASH	= 0x2B,
	KEY_Z			= 0x2C,
	KEY_X			= 0x2D,
	KEY_C			= 0x2E,
	KEY_V			= 0x2F,
	KEY_B			= 0x30,
	KEY_N			= 0x31,
	KEY_M			= 0x32,
	KEY_COMMA		= 0x33,
	KEY_PERIOD		= 0x34,
	KEY_SLASH		= 0x35,
	KEY_RSHIFT		= 0x36,
	KEY_MULTIPLY	= 0x37,
	KEY_LALT		= 0x38,
	KEY_SPACE		= 0x39,
	KEY_CAPSLOCK	= 0x3A,
	KEY_F1			= 0x3B,
	KEY_F2			= 0x3C,
	KEY_F3			= 0x3D,
	KEY_F4			= 0x3E,
	KEY_F5			= 0x3F,
	KEY_F6			= 0x40,
	KEY_F7			= 0x41,
	KEY_F8			= 0x42,
	KEY_F9			= 0x43,
	KEY_F10			= 0x44,
	KEY_NUMLOCK		= 0x45,
	KEY_SCROLL		= 0x46,
	KEY_NUMPAD7		= 0x47,
	KEY_NUMPAD8		= 0x48,
	KEY_NUMPAD9		= 0x49,
	KEY_SUBTRACT	= 0x4A,
	KEY_NUMPAD4		= 0x4B,
	KEY_NUMPAD5		= 0x4C,
	KEY_NUMPAD6		= 0x4D,
	KEY_ADD			= 0x4E,
	KEY_NUMPAD1		= 0x4F,
	KEY_NUMPAD2		= 0x50,
	KEY_NUMPAD3		= 0x51,
	KEY_NUMPAD0		= 0x52,
	KEY_DECIMAL		= 0x53,
	KEY_F11			= 0x57,
	KEY_F12			= 0x58,
	KEY_F13			= 0x64,
	KEY_F14			= 0x65,
	KEY_F15			= 0x66,
	KEY_KANA		= 0x70,
	KEY_CONVERT		= 0x79,
	KEY_NOCONVERT	= 0x7B,
	KEY_YEN			= 0x7D,
	KEY_NUMPADEQUALS= 0x8D,
	KEY_CIRCUMFLEX	= 0x90,
	KEY_AT			= 0x91,
	KEY_COLON		= 0x92,
	KEY_UNDERLINE	= 0x93,
	KEY_KANJI		= 0x94,
	KEY_STOP		= 0x95,
	KEY_AX			= 0x96,
	KEY_UNLABELED	= 0x97,  2`
	KEY_NUMPADENTER	= 0x9C,
	KEY_RCONTROL	= 0x9D,
	KEY_NUMPADCOMMA	= 0xB3,
	KEY_DIVIDE		= 0xB5,
	KEY_SYSRQ		= 0xB7,
	KEY_RALT		= 0xB8,
	KEY_PAUSE		= 0xC5,
	KEY_HOME		= 0xC7,
	KEY_UP			= 0xC8,
	KEY_PRIOR		= 0xC9,
	KEY_LEFT		= 0xCB,
	KEY_RIGHT		= 0xCD,
	KEY_END			= 0xCF,
	KEY_DOWN		= 0xD0,
	KEY_NEXT		= 0xD1,
	KEY_LWIN		= 0xDB,
	KEY_RWIN		= 0xDC,
	KEY_APPS		= 0xDD,

	// Alternate names for keys, to facilitate transition from DOS.
	KEY_ESC			= KEY_ESCAPE,
	KEY_ENTER		= KEY_RETURN,
	KEY_BACKSPACE	= KEY_BACK,
	KEY_NUMPADSTAR	= KEY_MULTIPLY,
	KEY_NUMPADMINUS	= KEY_SUBTRACT,
	KEY_NUMPADPLUS	= KEY_ADD,
	KEY_NUMPADPERIOD= KEY_DECIMAL,
	KEY_NUMPADSLASH	= KEY_DIVIDE,
	KEY_UPARROW		= KEY_UP,
	KEY_PGUP		= KEY_PRIOR,
	KEY_LEFTARROW	= KEY_LEFT,
	KEY_RIGHTARROW	= KEY_RIGHT,
	KEY_DOWNARROW	= KEY_DOWN,
	KEY_PGDN		= KEY_NEXT,

	MOUSE_NONE		= 0x000,
	MOUSE_KEYS		= 0x100,
	MOUSE0			= MOUSE_KEYS<<0,
	MOUSE1			= MOUSE_KEYS<<1,
	MOUSE2			= MOUSE_KEYS<<2,
	MOUSE3			= MOUSE_KEYS<<3,
	MOUSE4			= MOUSE_KEYS<<4,
	MOUSE5			= MOUSE_KEYS<<5,
	MOUSE6			= MOUSE_KEYS<<6,
	MOUSE7			= MOUSE_KEYS<<7,
	MOUSE_LEFT		= MOUSE0,
	MOUSE_RIGHT		= MOUSE1,
	MOUSE_MIDLE		= MOUSE2,

	COMPLEX_KEYS	= 0x00010000,
	KEY_CONTROL		= COMPLEX_KEYS+0,
	KEY_ALT			= COMPLEX_KEYS+1,
	KEY_SHIFT		= COMPLEX_KEYS+2,

	KF_SHIFT		= 0x01000000,
	KF_CTRL			= 0x02000000,
	KF_ALT			= 0x04000000,
	KF_DOUBLE		= 0x08000000,
	KF_NOSHIFT		= KF_SHIFT<<4,
	KF_NOCTRL		= KF_CTRL<<4,
	KF_NOALT		= KF_ALT<<4,
	KF_NODOUBLE		= KF_DOUBLE<<4,
	KF_KEYMASK		= 0x00ffffff,
	KF_FLAGSMASK	= ~KF_KEYMASK

	*/

};

#else 
typedef unsigned XKEY;
#endif



/*

	XKeyboardState() {}
	XKeyboardState(XKEY key_) {

		key = key_;
		bCTRL = bSHIFT = bALT = false;

	}

	bool isActive() const { return(active); }

	bool operator <(const XKeyboardState & keyboardState) const { return(key < keyboardState.key); }


};
*/



#endif
