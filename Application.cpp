
#include "stdafx.h"
#include "Application.hpp"
#include "Asset.hpp"

#define FRAMEWORK_WINDOW_WIDTH 1024
#define FRAMEWORK_WINDOW_HEIGHT 768
#define FRAMEWORK_CLASS_NAME L"ApplicationClass"
#define FRAMEWORK_WINDOW_NAME L"ApplicationWindow"

Application* Application::gApplication = NULL;





class AudioClipAsset : public Asset {

public:

	AudioClipAsset() {}
	~AudioClipAsset() {}

	static AudioClipAsset* Create(const AssetName& name, bool recreate = false) { 	

		Asset* asset = Asset::Find( name );

		//if(asset && dynamic_cast<AudioClipAsset>(asset) ) return (AudioClipAsset*)asset;
		if(asset && (AudioClipAsset*)asset ) return (AudioClipAsset*)asset;

		AudioClipAsset* newAudioClipAsset = new AudioClipAsset;
		//Asset::Add( name, newAudioClipAsset );
		return newAudioClipAsset; 
	}

};




void Application::processKeyboard(unsigned key) {

	switch (key) {

		case VK_F1:
			resize(800, 600);
			break;

		case VK_F2:
			resize(1280, 1024);
			break;
	};
}


void Application::SmartPtrresh() {

	if( !gApplication ) return;

	/*
	if(RenderSystem::GetCurrent()) {
			RenderSystem::GetCurrent()->beginFrame();
			extern void DrawTest(RenderSystem*);
			extern void DrawTexturedCubeTest(RenderSystem*);
			//DrawTest(RenderSystem::GetCurrent());
			DrawTexturedCubeTest(RenderSystem::GetCurrent());
			RenderSystem::GetCurrent()->endFrame();
	}
	*/

/*	
	renderSystem->getCanvas()->clear( Color::GRAY );
	renderSystem->getCanvas()->drawRect( 50, 0, 150, 150, Color::GREEN );
	renderSystem->getCanvas()->drawRect( 200 + 50, 0, 150, 150, Color::RED );
	renderSystem->getCanvas()->drawRect( 400 + 50, 0, 150, 150, Color::BLUE );


	renderSystem->getCanvas()->drawLine( 300, 300, 400, 350, Color::BLUE );
	renderSystem->getCanvas()->drawLine( 300, 301, 400, 351, Color::RED );
	renderSystem->getCanvas()->drawLine( 300, 302, 400, 352, Color::GREEN );
	renderSystem->getCanvas()->drawLine( 300, 303, 400, 353, Color::WHITE );
*/

	//renderSystem->endFrame();

}

void Application::resize(uint32 width, uint32 height) {

	//MoveWindow( hApplicationWnd, 0, 0, width, height, TRUE);
	//RenderSystem::GetCurrent()->resize( width, height );

}

void Application::mainLoop() {

  MSG msg;
  HACCEL hAccelTable = 0;	

  do {

      if( !PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {                               

          //update();
          //gApplication->SmartPtrresh();

      } else {

         if( msg.message == WM_PAINT ) {
             //gApplication->SmartPtrresh();
             //update();             
         }

         if( msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE ) {                          
							//gApplication->close();
             break;
         }


         if( msg.message == WM_QUIT ) {                          
             break;
         }

         if( !TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) ) {

             TranslateMessage( &msg );
             DispatchMessage( &msg );

         }

      }	       

			/*
			if( gApplication->isClosed() ) {
					break;
			}
			*/

   } while( true );

}

#if 0
void  Application::run() {

#if defined(DEBUG) || defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	gApplication = this;
	//coreSystem = CreateCoreSystem();

	//coreSystem->getLogger()->write( "Sys", "Application created..." );
   
	//renderSystem = CreateRenderSystem();
	
  //AsyncTaskInfo info;
	//SmartPtr<AsyncTask>  task = coreSystem->getFileSystemManager()->createAsyncTask( info );

	createApplicationWindowClass();
	createApplicationWindow();

	//RenderArea renderArea;
	//renderArea.hWnd = hApplicationWnd;
	//renderSystem->init( coreSystem, renderArea );
	/*
	RenderArea renderArea;
	renderArea.hWnd = hApplicationWnd;
	RenderSystem::Create(renderArea);
	RenderSystem::GetCurrent()->setRenderArea( renderArea );
	VideoMode videoMode;
	RenderSystem::GetCurrent()->setVideoMode(videoMode);
	*/
	
 
	mainLoop();
	
	//renderSystem->finit();
	//coreSystem->finit();

}
#endif


void Application::stop() {

}


extern RenderModule* CreateRenderModule();
extern Renderer* CreateDX11Renderer();
extern void RenderTest1();
extern void AudioTest1();

int APIENTRY Application::run(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow) {

#if defined(DEBUG) || defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	AudioTest1();
	RenderTest1();

	SharedPtr<AudioClipAsset> audioClipAsset = AudioClipAsset::Create("1.wav");
	audioClipAsset = NULL;
	//AudioClipAsset::Remove("1.wav");

	


	Window::SetInstance(hInstance);

	mainWindow = new AppWindow;
	mainWindow->create();	
	mainWindow->show();
	mainWindow->move(300, 200);

	//renderModule = CreateRenderModule();
	//renderModule->setWindow(mainWindow);
	renderer = CreateDX11Renderer();
	RenderArea renderArea;
	renderArea.hWnd = mainWindow->getHWND();
	renderer->initialize(renderArea);
	VideoMode videoMode;
	videoMode.width = 800;
	videoMode.height = 600;
	//renderer->setVideoMode(videoMode);

	mainLoop();

	renderer->shutdown();
	renderModule = NULL;

	mainWindow = NULL;

	return 0;
}




void Log( const char* formatString, ...  ) {

  va_list argList;
  char outputString[ 4096 ];

  va_start( argList, formatString );
  vsprintf( outputString, formatString, argList );
  va_end( argList );

  OutputDebugStringA( outputString );
	OutputDebugStringA( "\n" );

}
