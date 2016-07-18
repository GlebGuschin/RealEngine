#pragma once

#ifndef __RM_HPP__
#define __RM_HPP__

/*
#include "Asset.hpp"
*/

#include "Module.hpp"
#include "Window.hpp"
#include "Canvas.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "Mesh.hpp"
#include "RenderScene.hpp"
#include "MaterialManager.hpp"


//inline template<T> T* Cast<T>()









/*
class ModuleListener : public Listener {

public:

	virtual void onStart() = 0;
	virtual void onStop() = 0;

};

class Module : public Referenced {

	virtual bool isLoading() const { return false; }

public:

	static Module* LoadModule( const String& ) { return NULL; }

};

class ModuleManager111 : public Referenced {

public:
};
*/












/*
enum VERTEX_TYPE2 {
	VERTEX_COMMON,
	VERTEX_P3F_N3F_TCF2
};
*/


struct GeometryInfo {
	unsigned flags;
	//VERTEX_TYPE vertexType;
	INDEX_TYPE indexType;
};

/*
class Geometry : public Referenced {
	
	GeometryInfo info;

public:

};
*/








class RenderModule : public Module {

	SharedPtr<Window> renderWindow;

public:

	virtual void setWindow(Window*) = 0;
	//virtual bool setVideoMode(const VideoMode&) = 0;

	virtual void beginFrame() = 0;
	virtual void endFrame() = 0;

	virtual MaterialManager* getMaterialManager() const =0; 
	virtual TextureManager* getTextureManager() const =0;
	//virtual MeshManager* getMeshManager() const =0;

	//virtual RenderScene* createScene() = 0;
	//virtual MaterialManager* getMaterialManager()=0; 



	/*
	virtual Geometry* createGeometry(unsigned flags, VERTEX_TYPE vertexType, unsigned numVertices, INDEX_TYPE indexType = INDEX_NONE, unsigned numIndices = 0) = 0;
	virtual Texture* createTexture(const TextureInfo&) = 0;
	virtual Texture* createTexture(const AssetName&, bool reload=false) = 0;

	virtual Material* createMaterial() = 0;
	virtual Material* createMaterial(Material*) = 0;
	virtual Material* createMaterial(const AssetName&) = 0;

	virtual Font* createFont(const FontInfo&) = 0;
	virtual Font* createFont(const AssetName) = 0;


	virtual RenderScene* createScene() = 0;
	virtual Canvas* createCanvas() { return NULL; }
	*/

};


RenderModule* CreateRenderModule();




#endif