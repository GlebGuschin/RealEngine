#pragma once

#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

class WindowListener : public Listener {

	virtual void onPaint()=0;

};


struct WindowInfo {
	int width, height;
};

class Window : public Referenced {

protected:

	HWND hWnd;

	static HINSTANCE hInstance;
	

	bool	visible;
	bool	active;
	
	WindowInfo info;

	//XMouseState mouseState;
	///XInputAction inputAction;
	//bool bHasInputAction;
	//render::XRenderArea renderArea;

	struct Atom {
		ATOM atom;
		uint rc;
		Atom() { atom = 0; rc = 0; }
	};

	typedef std::map<std::wstring, Atom> ClassMapType;
	static ClassMapType ClassMap;	
	typedef std::map<HWND, Window*> WindowMapType;
	static WindowMapType WindowMap;

	//LPCWSTR windowClass;
	
	virtual LPCWSTR getClassName() const { return(L"Window"); }
	virtual WNDPROC getClassFunc() const { return(&WndProc); };

	virtual void onPaint();

	virtual void onMouseButton(int x, int y, MOUSE_BUTTON_TYPE buttonType, INPUT_ACTION_TYPE actionType );
	virtual void onMouseMove(int x, int y);
	virtual void onMouseWheel(int x, int y, int value);

	virtual void onKeyboard(KEY_TYPE buttonType, INPUT_ACTION_TYPE actionType, unsigned modificators = 0);

	static bool RegisterWindowClass(WNDPROC lpfnWndProc, LPCWSTR lpszClassName);
	static Window* FindWindow(HWND hWnd);
	static void AddWindow(HWND hWnd, Window*);
	static void RemoveWindow(HWND hWnd);

	void setVisible(bool visible_);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	//Window() {}
	HWND getHWND() const { return hWnd; }

	void create(const WindowInfo&);
	void create();
	void destroy();
	void show();
	void hide();
	void update();
	void move(int x, int y);

	static void SetInstance(HINSTANCE hInstance_) { hInstance = hInstance_; }

	void addListener(WindowListener*);
	void removeListener(WindowListener*);

};





class AppWindow : public Window {

	LPCWSTR getClassName() const { return(L"ApplicationWindow"); }
	
public:

	//void onPaint() {}

};



#endif
