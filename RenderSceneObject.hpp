#pragma once

#ifndef __RSO_HPP__
#define __RSO_HPP__

#include "RenderCommon.hpp"
#include "Material.hpp"
#include "Geometry.hpp"


//class GpuTexture;

class RenderSceneView {

	Projection projection;
	Viewport viewport;
	Transform cameraTransform;

public:

	RenderSceneView() {}
	RenderSceneView(const Transform& cameraTransform_, const Viewport& viewport_, const Projection& projection_) {}

	const Projection& getProjection() const { return projection; }
	const Viewport& getViewport() const { return viewport; }

};



class RenderScene;
class RenderSceneObject;

class RenderSurface {
	
	SharedPtr<Material> material;
	SharedPtr<Geometry> geometry;

public:

	RenderSurface() {}
	RenderSurface(Geometry* geometry_, Material* material_) : geometry(geometry_), material(material_) {}

	void setMaterial(Material* material_) { material = material_; }

	Material* getMaterial() const { return material; }
	Geometry* getGeometry() const { return geometry; }

};

#if 1
enum RENDER_OBJECT_TYPE {
	RENDER_OBJECT_DEFAULT = 1,
	RENDER_OBJECT_TWO_SIDE = 2,
	RENDER_OBJECT_ALPHA_TEST = 4,
	RENDER_OBJECT_REFRACTION = 8,	
	//RENDER_OBJECT_BUCKET_MAX
};
#else
enum RENDER_OBJECT_TYPE {
	RENDER_OBJECT_DEFAULT = 0,
	RENDER_OBJECT_TWO_SIDE = 1,
	RENDER_OBJECT_ALPHA_TEST = 2,
	RENDER_OBJECT_REFRACTION = 3,
	//RENDER_OBJECT_BUCKET_MAX
};
#endif


class RenderObject {

	Transform transform;
	RenderSurface surface;

	unsigned modificators;

public:

	unsigned getModificators() const { return modificators; }
	void setModificators(unsigned modificators_)  { modificators = modificators_; }

	const RenderSurface& getSurface() const { return surface; }
	void setSurface(const RenderSurface& surface_) { surface = surface_ ; }

	void setTransform(const Transform& transform_) { transform = transform_; }
	const Transform& getTransform() const { return transform; }

	bool operator==(const RenderObject& other) const { return transform == other.transform; }

	RenderObject(const Transform& transform_, const RenderSurface& surface_, unsigned) {}
	RenderObject() {}

};




struct RenderPass {
	int renderStates;
	int renderTarget;
};


class RenderPassContext {

	RenderSceneView renderSceneView;

	//DynamicArray<RenderObject> renderObjects;
	//std::vector<RenderObject> renderObjects[RENDER_OBJECT_BUCKET_MAX];
	std::vector<RenderObject> renderObjects;
	//std::vector<RenderObject> renderObjects;

public:

	void setSceneView(const RenderSceneView& renderSceneView_) { renderSceneView = renderSceneView_; }

	//void addRenderObject(const RenderObject& renderObject, RENDER_OBJECT_BUCKET_TYPE type = RENDER_OBJECT_BUCKET_DEFAULT)  { renderObjects.push_back(renderObject); }
	void addRenderObject(const RenderObject& renderObject)  { renderObjects.push_back(renderObject); }

	//size_t getNumRenderObjects(RENDER_OBJECT_BUCKET_TYPE type = RENDER_OBJECT_BUCKET_DEFAULT) const { return renderObjects.size(); }
	unsigned getNumRenderObjects() const { return (unsigned)renderObjects.size(); }
	//const RenderObject& getRenderObject(unsigned index, RENDER_OBJECT_BUCKET_TYPE type = RENDER_OBJECT_BUCKET_DEFAULT) const { return renderObjects[index]; }
	const RenderObject& getRenderObject(unsigned index) const { return renderObjects[index]; }

};

class BaseRenderPassContext : public RenderPassContext {
public:	

};

class OpacityRenderPassContext : public RenderPassContext {
public:

};


class ShadowRenderPassContext : public RenderPassContext {
public:	

};

class TranslucentRenderPassContext : public RenderPassContext {
public:

};

/*
class RefractionRenderPassContext : public RenderPassContext {
public:
};
*/









class RenderSceneObjectListener : public Listener {
public:
	virtual void onChangedTransform(RenderSceneObject*)=0;
};

typedef SharedPtr<RenderSceneObjectListener> RenderSceneObjectListenerPtr;



struct RenderObjectShadowInfo {
	bool caster, reciever;
	float bias;
};



class RenderSceneObject : public Referenced {

	Transform transform;

	DynamicArray<RenderSceneObjectListenerPtr> listeners;

	bool shadowCaster, shadowReciever;

	BoxSphereBounds boxSphereBounds;

public:

	RenderSceneObject() {}

	bool isShadowCaster() const { return shadowCaster; }

	virtual void addListener(RenderSceneObjectListener* listener) { listeners.add(listener); }
	virtual void removeListener(RenderSceneObjectListener* listener) { listeners.remove(listener);}

	const Transform& getTransform() const { return transform; }

	virtual void setTransform( const Transform& transform_) {
		transform = transform_; 
		for(unsigned i = 0; i < listeners.size(); i++) listeners[i]->onChangedTransform(this);
	
	}; 

	virtual RenderScene* getScene() const { return NULL; };

	virtual void processPass(BaseRenderPassContext&);
	virtual void processPass(OpacityRenderPassContext&);
	virtual void processPass(ShadowRenderPassContext&);
	virtual void processPass(TranslucentRenderPassContext&);

	virtual void update(float) {}
	
};

typedef SharedPtr<RenderSceneObject>  RenderSceneObjectPtr;


class TestRenderSceneObject : public RenderSceneObject {

public:
	
	void processPass(BaseRenderPassContext&);
	void processPass(OpacityRenderPassContext&);
	void processPass(ShadowRenderPassContext&);
	void processPass(TranslucentRenderPassContext&);

	struct TestItem {
		SharedPtr<Material> material;
		SharedPtr<Geometry> geometry;
	};

	DynamicArray< TestItem> items;

};



#endif