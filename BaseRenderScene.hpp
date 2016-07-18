#pragma once

#ifndef __BASE_RENDER_SCENE_HPP__
#define __BASE_RENDER_SCENE_HPP__

#include "RenderScene.hpp"


class BaseRenderScene : public RenderScene {

protected:

	DynamicArray<SharedPtr<RenderSceneObject>> objects;

	DynamicArray<SharedPtr<MeshRenderSceneObject>>  meshes;
	DynamicArray<SharedPtr<LightRenderSceneObject>> lights;
	DynamicArray<SharedPtr<ParticleSystemRenderSceneObject>> particleSystems;

	SharedPtr<LightRenderSceneObject> sunLight;

	SharedPtr<OctreeNode> root;

	DynamicArray<SharedPtr<OcclusionArea>> occlusionAreas;

	//void addRenderComponent(RenderComponent*) {}
	//void removeRenderComponent(RenderComponent*) {}
	void onChangedTransform(RenderSceneObject*) {}

	virtual void addSceneObject(RenderSceneObject* light) {}
	virtual void removeSceneObject(RenderSceneObject* light) {}

public:

	void addListener(RenderSceneListener*) {}
	void removeListener(RenderSceneListener*) {}

	//size_t getNumRenderObjects() const { return objects; }
	//const DynamicArray<SharedPtr<RenderSceneObject>>& getSceneObjects() const { return objects; }
	void getMeshes(DynamicArray<SharedPtr<MeshRenderSceneObject>>&);
	void getLights(DynamicArray<SharedPtr<LightRenderSceneObject>>&);
	void getParticleSystems(DynamicArray<SharedPtr<ParticleSystemRenderSceneObject>>&);
	void getOcclusionAreas(DynamicArray<SharedPtr<OcclusionArea>>&);

	

	void addLight(LightRenderSceneObject*);
	void removeLight(LightRenderSceneObject*);
	LightRenderSceneObject* getSunLight() { return sunLight; }

	void addMesh(MeshRenderSceneObject*);
	void removeMesh(MeshRenderSceneObject*);

	void addParticleSystem(ParticleSystemRenderSceneObject*);
	void removeParticleSystem(ParticleSystemRenderSceneObject*);

	void addOcclusionArea(OcclusionArea*);
	void removeOcclusionArea(OcclusionArea*);
	

	void addOctreeNode(OctreeNode*, OctreeNode* parent=NULL) {}
	void removeOctreeNode(OctreeNode*) {}

};


#endif