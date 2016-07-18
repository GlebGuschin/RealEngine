#pragma once

#ifndef __GLRENDERER_HPP__
#define __GL11RENDERER_HPP__

#include "Renderer.hpp"

#include <windows.h>

/*
class DX11HardwareTexture : public HardwareTexture {

	ID3D11Texture2D* pTexture2D;
	ID3D11ShaderResourceView* pSRV;

public:

	
	DX11HardwareTexture( const HardwareTextureInfo& info_, ID3D11Texture2D* pTexture2D_) :
		pTexture2D(pTexture2D_), pSRV(NULL), HardwareTexture( info_) {}

	DX11HardwareTexture( const HardwareTextureInfo& info_, ID3D11ShaderResourceView* pSRV_) :
		pSRV(pSRV_), pTexture2D(NULL), HardwareTexture(info_) {}

	//~DX11HardwareTexture() { renderDevice->releaseTexture(this); }

};

*/



class GLRenderer : public Renderer {

	HWND hWnd;
	VideoMode videoMode;


public:

	GLRenderer() :{} 

	bool initialize(const RenderArea&);
	void shutdown();

	//virtual RenderScene* createScene() = 0;

	HardwareTexture* createTexture(const HardwareTextureInfo&);
	
	bool setVideoMode(const VideoMode&);
	void setRenderArea(const RenderArea&);

	void drawScene(RenderScene* renderScene, const RenderSceneView& );
	void drawText(const String&, int x, int y);

	void beginFrame();
	void endFrame();


};

Renderer* GetRenderer();

extern Renderer* CreateGL11Renderer();

#endif