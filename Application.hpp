#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__


#include "Common.hpp"
#include "Referenced.hpp"
#include "Name.hpp"
#include "Window.hpp"

#include "RenderModule.hpp"
#include "Renderer.hpp"
//#include "RenderSystem.hpp"




class InputActionInfo {
protected:
	bool valid;
public:
	bool isValid() const { return valid; }
	InputActionInfo() : valid(false) {}
};

class MouseActionInfo : public InputActionInfo {		
public:
	
};

class KeyboardActionInfo : public InputActionInfo {
public:

};


class InputAction {
	MouseActionInfo mouseActionInfo;
	KeyboardActionInfo keyboardActionInfo;
public:
	const MouseActionInfo& getMouseActionInfo() const { return mouseActionInfo; };
	const KeyboardActionInfo& getKeyboardActionInfo() const { return keyboardActionInfo; };
};


class Application : public Referenced {

protected:

	static Application* gApplication;


	SharedPtr<Window> mainWindow;

  HINSTANCE hInstance;	

  virtual void mainLoop();

  void resize( uint32 width, uint32 height);
  ///MouseState mouseState;
  //render::XVideoMode videoMode;
	//application::IApplication *createApplication();
  std::fstream logFileStream;
	
	virtual bool isClosed() const { return( false ); };
	virtual void update() {};
	virtual void SmartPtrresh();
	virtual void processKeyboard(unsigned);
	

	SharedPtr<RenderModule> renderModule;
	SharedPtr<Renderer> renderer;	

public:

	int APIENTRY run(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow);
	void stop();


};



#endif
