#pragma once

#ifndef __DX11RENDERER_HPP__
#define __DX11RENDERER_HPP__

#include "BaseRenderer.hpp"

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

struct GlobalConstantBuffer {	
	XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
};


struct ShaderProgram {

	ID3D11VertexShader*    pVertexShader;
	ID3D11PixelShader*     pPixelShader;

	ShaderProgram() : pVertexShader(NULL), pPixelShader(NULL) {}

};


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




class DX11Renderer : public BaseRenderer {

	HWND hWnd;
	VideoMode videoMode;

	ID3D11DeviceContext* pImmediateContext;
	ID3D11Device*  pd3dDevice;
	IDXGISwapChain*         pSwapChain;
	ID3D11RenderTargetView* pRenderTargetView;
	ID3D11VertexShader*     pVertexShader;
	ID3D11PixelShader*      pPixelShader;
	
	ID3D11Buffer*           pVertexBuffer;

	struct ShaderCompileInfo {
		Name name;
		void* macros;
		SHADER_TYPE shaderType;	
	};

	ID3D10Blob* compileShader(const ShaderCompileInfo& shaderCompileInfo);

	

public:

	DX11Renderer() : pImmediateContext(NULL), pd3dDevice(NULL) {} 

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

extern Renderer* CreateDX11Renderer();

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x) x->Release(); x = NULL;
#endif


#endif