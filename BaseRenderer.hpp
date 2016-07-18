#pragma once

#ifndef __BASE_RENDERER_HPP__
#define __BASE_RENDERER_HPP__

#include "Renderer.hpp"

class BaseRenderer : public Renderer {

	DynamicArray<SharedPtr<RendererListener>> listeners;
	
	DynamicArray<HardwareTexture*> textures;

	DynamicArray<SharedPtr<RenderScene>> scenes;

protected:		

	RendererStatistic statistic;
	RENDERER_STATE_TYPE state;
	VideoMode videoMode;
	
	void registerTexture(HardwareTexture*);
	void unregisterTexture(HardwareTexture*);

	void registerScene(RenderScene*);
	void unregisterScene(RenderScene*);

public:

	BaseRenderer() : state(RENDERER_STATE_UNINITILAIZED) {}

	void addListener(RendererListener* listener) { listeners.add(listener); }
	void removeListener(RendererListener* listener) { listeners.remove(listener); }

	RenderScene* createScene();
	void releaseScene(RenderScene*);

	bool initialize(const RenderArea&);
	void shutdown();

	HardwareTexture* createTexture(const HardwareTextureInfo&);
	void releaseTexture(HardwareTexture*);
	HardwareVertexBuffer* createVertexBuffer(const HardwareVertexBufferInfo&);
	HardwareIndexBuffer* createIndexBuffer(const HardwareIndexBufferInfo&);

	bool setVideoMode(const VideoMode&) { return true;}
	void setRenderArea(const RenderArea&) {}

	void drawScene(RenderScene* renderScene, const RenderSceneView&) {}
	void drawText(const String&, int x, int y) {}

	void beginFrame();
	void endFrame();

};






#endif