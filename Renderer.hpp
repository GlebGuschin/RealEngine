#pragma once

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__


#include "HardwareTexture.hpp"
#include "HardwareVertexBuffer.hpp"
#include "HardwareIndexBuffer.hpp"
#include "RenderScene.hpp"


struct VideoMode {
	unsigned width, height, bits;
	bool fullscreen;
	bool vsync;

	VideoMode(unsigned width_, unsigned height_, unsigned bits_, bool fullscreen_ = false, bool vsync_ = false) :
		width(width_), height(height_), bits(bits_), vsync(vsync_), fullscreen(fullscreen_) {}

	VideoMode() : width(800), height(600), bits(32), vsync(false), fullscreen(false) {}

	bool operator == (const VideoMode &videoMode_) const {
		return(width != videoMode_.width || height != videoMode_.height || vsync != videoMode_.vsync || bits != videoMode_.bits || fullscreen != videoMode_.fullscreen);
	}

};

struct RenderArea {
	HWND hWnd;
};

enum SHADER_TYPE { SHADER_VERTEX, SHADER_FRAGMENT };

//extern Renderer* gRenderer; 

struct RendererStatistic {
	unsigned currentFrame;
	RendererStatistic() : currentFrame(0) {}
};


class RendererListener : public Listener {
public:
	virtual void onBeginFrame() {}
	virtual void onEndFrame() {}
	virtual void onChangeMode() {}
};

enum RENDERER_STATE_TYPE {
	RENDERER_STATE_UNINITILAIZED = 0
};

class Renderer : public Referenced {

	//DynamicArray<SharedPtr<RendererListener>> listeners;

protected:

	//RendererStatistic statistic;
	//RENDERER_STATE_TYPE state;
	//VideoMode videoMode;

public:

	//Renderer() : state(RENDERER_STATE_UNINITILAIZED) {}

	virtual void addListener(RendererListener* listener)=0;
	virtual void removeListener(RendererListener* listener)=0;

	virtual RenderScene* createScene()=0;
	virtual void releaseScene(RenderScene*)=0;

	virtual bool initialize(const RenderArea&)=0;
	virtual void shutdown()=0;

	virtual HardwareTexture* createTexture(const HardwareTextureInfo&)=0;
	virtual void releaseTexture(HardwareTexture*) {}
	virtual HardwareVertexBuffer* createVertexBuffer(const HardwareVertexBufferInfo&) {return NULL;}
	virtual void releaseVertexBuffer(HardwareVertexBuffer*) {}
	virtual HardwareIndexBuffer* createIndexBuffer(const HardwareIndexBufferInfo&) {return NULL;}
	virtual void releaseInexBuffer(HardwareIndexBuffer*) {}
	
	virtual bool setVideoMode(const VideoMode&)=0;
	virtual void setRenderArea(const RenderArea&)=0;

	virtual void drawScene(RenderScene* renderScene, const RenderSceneView& )=0;
	virtual void drawText(const String&, int x, int y)=0;

	virtual void beginFrame()=0;
	virtual void endFrame()=0;

};






#endif