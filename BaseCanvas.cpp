#include "stdafx.h"
#include "Canvas.hpp"


class BaseCanvas : public Canvas {

	//SharedPtr<RenderScene> renderScene;

public:

	BaseCanvas( RenderScene* renderScene) : Canvas(renderScene) {}

	void drawLine( int x1, int y1, int x2, int y2, const Color& color ) {}
	void drawRectangle( int x1, int y1, int x2, int y2, const Color& color ) {}
	void drawText(int x1, int y1, const String&, const Color& color, Font* font) {}

	void setDefaultFont( Font* ) {}
	void flush() {}

};

Canvas* CreateCanvas(RenderScene*renderScene ) {  return new BaseCanvas(renderScene); }

