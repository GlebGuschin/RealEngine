#pragma once

#ifndef __CANVAS_HPP__
#define __CANVAS_HPP__

#include "Common.hpp"
#include "Color.hpp"
#include "String.hpp"
#include "Referenced.hpp"
#include "Font.hpp"
#include "RenderScene.hpp"
#include "Material.hpp"


class Canvas : public Referenced {

	SharedPtr<RenderScene> renderScene;

public:

	Canvas(RenderScene* renderScene_ ):renderScene(renderScene_) {} 

	//void setScene( RenderScene*) {}

	virtual void drawLine( int x1, int y1, int x2, int y2, const Color& color = Color::WHITE ) {}
	virtual void drawRectangle( int x1, int y1, int x2, int y2, const Color& color = Color::WHITE ) {}
	virtual void drawText(int x1, int y1, const String&, const Color& color = Color::WHITE, Font* font = NULL) {}

	virtual void setDefaultFont( Font* ) {}

	virtual void flush() {}

};

Canvas* CreateCanvas(RenderScene*);

#endif