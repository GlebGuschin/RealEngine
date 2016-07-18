#include "stdafx.h"
#include "DX11Renderer.hpp"



	//virtual RenderScene* createScene() = 0;

D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11InputLayout*      pVertexLayout = NULL;
ID3D11Resource*         pGlobalTexture= NULL;

ID3D11Buffer*						pVertexBuffer = NULL;

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx11.lib" )



bool DX11Renderer::initialize(const RenderArea& renderArea) { 

	HRESULT hr = S_OK;
	HWND hWnd = renderArea.hWnd;
	RECT rc;
	GetClientRect( hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_WARP,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pImmediateContext);
		if (SUCCEEDED(hr))
			break;
	}

	//if (FAILED(hr))
		//return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	//if (FAILED(hr))
		//return hr;

	hr = pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	pBackBuffer->Release();
	//if (FAILED(hr))
		//return hr;

	pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pImmediateContext->RSSetViewports(1, &vp);


	//renderDevice = new DX11RenderDevice(pd3dDevice, pImmediateContext);

	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	D3DX11_IMAGE_INFO ImageInfo;

	D3DX11GetImageInfoFromFileA("Adv.dds", NULL,  &ImageInfo, &hr);
	//D3DX11CreateTextuSmartPtrromFileA(pd3dDevice, "Adv.dds", &LoadInfo, NULL, &pGlobalTexture, &hr );
	D3DX11CreateTextureFromFileA(pd3dDevice, "Adv.dds", &LoadInfo, NULL, &pGlobalTexture, &hr );
	///D3DX11CreateTextuSmartPtrromFileA(pd3dDevice, "Particle.tga", &LoadInfo, NULL, &pGlobalTexture, &hr);

	int i = 0;
	D3DX11SaveTextureToFile(pImmediateContext, pGlobalTexture, D3DX11_IFF_DDS, L"texture2.dds");

	return true;

}

void DX11Renderer::shutdown() {

	SAFE_RELEASE(pGlobalTexture);
	
	if (pImmediateContext) pImmediateContext->ClearState();

	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pSwapChain);
	SAFE_RELEASE(pImmediateContext);
	SAFE_RELEASE(pd3dDevice);

}

HardwareTexture* DX11Renderer::createTexture(const HardwareTextureInfo& info ) { 

	ID3D11Texture2D* pTexture2D = NULL;
	DX11HardwareTexture* texture = new DX11HardwareTexture(info, pTexture2D);

	return texture;
}
	
bool DX11Renderer::setVideoMode(const VideoMode& videoMode_ ) {

	ID3D11RenderTargetView* pRenderTargetView2 = NULL;
	pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView2, NULL);
	SAFE_RELEASE(pRenderTargetView);
	
	pSwapChain->ResizeBuffers( 2, videoMode_.width, videoMode_.height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH );

	videoMode = videoMode_;

	return true;

}

void DX11Renderer::setRenderArea(const RenderArea& renderArea) {

	hWnd = renderArea.hWnd;

}

void DX11Renderer::beginFrame() {

	float ClearColor[4] = { 0.25f, 0.75f, 0.5f, 1.0f }; //red,green,blue,alpha
	pImmediateContext->ClearRenderTargetView(pRenderTargetView, ClearColor);

}

void DX11Renderer::endFrame() {

	pSwapChain->Present( 0, 0 );

}

void DX11Renderer::drawScene(RenderScene* renderScene, const RenderSceneView& ) {


}

void DX11Renderer::drawText(const String&, int x, int y) {


}

ID3D10Blob* DX11Renderer::compileShader(const ShaderCompileInfo& shaderCompileInfo) {

	HRESULT hr = S_OK;
	ID3DBlob* pBlobShader = NULL;
	ID3DBlob* pBlobError = NULL;

	ID3D11VertexShader*    pVertexShader = NULL;
	ID3D11PixelShader*     pPixelShader = NULL;

	// vertex shader
	//hr = D3DX11CompileFromMemory( (LPCSTR)shaderBodyPtr, vertexShaderBuffer->getSize(), NULL, NULL, NULL, "vs_main", "vs_4_0", 0, 0, NULL, &pBlobShader, &pBlobError, NULL );
	assert(hr==S_OK);
	//vertexShaderBuffer->unlock();

	return pBlobShader;

}

/*
	// Create the vertex shader
	hr = pd3dDevice->CreateVertexShader(pBlobShader->GetBufferPointer(), pBlobShader->GetBufferSize(), NULL, &pVertexShader);
	assert(hr == S_OK);
	
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12 + 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	if( !g_pVertexLayout ) {
		hr = pd3dDevice->CreateInputLayout(layout, numElements, pBlobShader->GetBufferPointer(), pBlobShader->GetBufferSize(), &g_pVertexLayout);
	}
	SAFE_RELEASE(pBlobShader);
	SAFE_RELEASE(pBlobError);

	// pixel shader
	//shaderBodyPtr = fragmentShaderBuffer->lock();
	hr = D3DX11CompileFromMemory((LPCSTR)shaderBodyPtr, fragmentShaderBuffer->getSize(), NULL, NULL, NULL, "ps_main", "ps_4_0", 0, 0, NULL, &pBlobShader, &pBlobError, NULL);
	assert(hr == S_OK);
	//fragmentShaderBuffer->unlock();

	// Create the pixel shader
	hr = pd3dDevice->CreatePixelShader(pBlobShader->GetBufferPointer(), pBlobShader->GetBufferSize(), NULL, &pPixelShader);
	assert(hr == S_OK);

	SAFE_RELEASE(pBlobShader);
	SAFE_RELEASE(pBlobError);

	//shaderProgram = new DX11HardwareShaderProgram(this, info, pVertexShader, pPixelShader);	
	//return shaderProgram;

}
*/

Renderer* gRenderer = NULL;
Renderer* CreateDX11Renderer() { gRenderer = new DX11Renderer; return gRenderer; }



Renderer* GetRenderer() { return gRenderer; }