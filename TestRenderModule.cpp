#include "stdafx.h"
#include "RenderModule.hpp"
#include "TextureManager.hpp"

#include <gl/gl.h>
#include <GL/glu.h>
//#include "glext.h"
//#include "wglext.h"

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )


/*

class TestRenderModule : public RenderModule {

	SharedPtr<Window> renderWindow;
	HGLRC context;

	//bool createContext( const VideoMode &videoMode_ );
	void destroyContext();

public:

	TestRenderModule() : context(NULL) {}
	

	void setWindow(Window*);
	bool setVideoMode(const VideoMode&);

	void beginFrame();
	void endFrame();

	MaterialManager* getMaterialManager() const { return NULL; }
	TextureManager* getTextureManager() const { return NULL; }
	MeshManager* getMeshManager() const { return NULL; }

};

void TestRenderModule::setWindow(Window* renderWindow_) {

	renderWindow = renderWindow_;

	VideoMode videoMode;
	const bool ok = createContext(videoMode);

}

void TestRenderModule::beginFrame() {

	glClearColor(1.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

}

void TestRenderModule::endFrame() {

	HWND hWnd = renderWindow->getHWND();
	HDC hDC = GetDC( hWnd );
  SwapBuffers( hDC );
  ReleaseDC( hWnd, hDC );

}

void TestRenderModule::destroyContext() {

   wglMakeCurrent( NULL, NULL );
   wglDeleteContext( context );
}

bool TestRenderModule::createContext( const VideoMode &videoMode_ ) {

	if( context ) { 	
			destroyContext();
  } 

   int pixelFormat;

   PIXELFORMATDESCRIPTOR pfd = {
      sizeof( PIXELFORMATDESCRIPTOR ),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      videoMode_.bits,
      0,
      0,
      0,
      0,
      0,
      0,
      8,
      0,
      0,
      0,
      0,
      0,
      0,
      24, // depth
      8,  // stencil
      0,
      PFD_MAIN_PLANE,
      0,
      0,
      0,
   };

   HDC hDC = GetDC( renderWindow->getHWND() );

   pixelFormat = ChoosePixelFormat( hDC, &pfd );
   SetPixelFormat( hDC, pixelFormat, &pfd );

   context = wglCreateContext( hDC );
   wglMakeCurrent( hDC, context );

   ReleaseDC( renderWindow->getHWND(), hDC );

	 return true;

}

bool TestRenderModule::setVideoMode(const VideoMode& videoMode_) {

	return createContext(videoMode_);

}

RenderModule* gRenderModule = NULL;

RenderModule* CreateRenderModule() { 
	gRenderModule = new TestRenderModule;
	return gRenderModule;
}


*/