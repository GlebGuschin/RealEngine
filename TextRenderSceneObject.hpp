#pragma once

#ifndef __TEXT_RENDER_OBJECT_HPP__
#define __TEXT_RENDER_SCENE_OBJECT_HPP__

#include "RenderSceneObject.hpp"

class TextRenderSceneObject : public RenderSceneObject {

	String text;

public:
	TextRenderSceneObject() {}	
	
	void setText(const String&) {}

};


#endif