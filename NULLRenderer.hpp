#pragma once

#ifndef __NULL_RENDERER_HPP__
#define __NULL_RENDERER_HPP__

#include "BaseRenderer.hpp"

// 954-90-30
class NULLRenderer : public BaseRenderer {

	HWND hWnd;
	VideoMode videoMode;

public:

	NULLRenderer() {}

	bool initialize(const RenderArea&);
	void shutdown();
	

	HardwareTexture* createTexture(const HardwareTextureInfo&);
	HardwareVertexBuffer* createVertexBuffer(const HardwareVertexBufferInfo&);
	HardwareIndexBuffer* createIndexBuffer(const HardwareIndexBufferInfo&);
	
	
	bool setVideoMode(const VideoMode&);
	void setRenderArea(const RenderArea&);

	void drawScene(RenderScene* renderScene, const RenderSceneView& );
	void drawText(const String&, int x, int y);

	void beginFrame();
	void endFrame();


};


#endif