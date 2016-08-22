#pragma once

#ifndef __RENDER_SCENE_HPP__
#define __RENDER_SCENE_HPP__

#include "DynamicArray.hpp"
#include "RenderCommon.hpp"
#include "RenderSceneObject.hpp"
#include "LightRenderSceneObject.hpp"
#include "MeshRenderSceneObject.hpp"
#include "ParticleSystemRenderSceneObject.hpp"
#include "TerrainRenderSceneObject.hpp"
#include "TextRenderSceneObject.hpp"


enum FOG_TYPE { FOG_LINEAR, FOG_EXP, FOG};

struct FogInfo { 
	Color color;
};

class OctreeNode;
enum OCTREE_NODE_TYPE {OCTREE_NODE_MAX=8};

class OctreeNode : public Referenced {

	SharedPtr<OctreeNode> children[OCTREE_NODE_MAX];

public:

	OctreeNode* getChildren(OCTREE_NODE_TYPE index) const { return children[index]; }

};




class RenderSceneListener : public Listener {

public:

};



class RenderScene : public RenderSceneObjectListener {

protected:

	DynamicArray<SharedPtr<RenderSceneObject>> objects;

	DynamicArray<SharedPtr<LightRenderSceneObject>> lights;
	SharedPtr<LightRenderSceneObject> sunLight;
	SharedPtr<TerrainRenderSceneObject> terrain;

	DynamicArray<SharedPtr<TestRenderSceneObject>> tests;

	DynamicArray<SharedPtr<MeshRenderSceneObject>> meshes;
	DynamicArray<SharedPtr<ParticleSystemRenderSceneObject>> particleSystems;

protected:

	void addRenderSceneObject(RenderSceneObject* rso) {}
	void removeRenderSceneObject(RenderSceneObject* rso) {}

	void onChangedTransform(RenderSceneObject*) {}

public:

	virtual void addListener(RenderSceneListener*) {}
	virtual void removeListener(RenderSceneListener*) {}

	//size_t getNumRenderObjects() const { return objects; }
	//const DynamicArray<SharedPtr<RenderSceneObject>>& getSceneObjects() const { return objects; }

	virtual void getObjects(DynamicArray<SharedPtr<MeshRenderSceneObject>>&) {}
	virtual void getMeshes(DynamicArray<SharedPtr<MeshRenderSceneObject>>&) {}
	virtual void getLights(DynamicArray<SharedPtr<LightRenderSceneObject>>&) {}
	virtual void getParticleSystems(DynamicArray<SharedPtr<ParticleSystemRenderSceneObject>>&) {}
	virtual void getOcclusionAreas(DynamicArray<SharedPtr<OcclusionArea>>&) {}
	

	virtual void addLight(LightRenderSceneObject* light) {}
	virtual void removeLight(LightRenderSceneObject* light) {}
	virtual LightRenderSceneObject* getSunLight() { return sunLight; }

	virtual void addMesh(MeshRenderSceneObject* ) {}
	virtual void removeMesh(MeshRenderSceneObject* ) {}

	virtual void addParticleSystem(ParticleSystemRenderSceneObject*) {}
	virtual void removeParticleSystem(ParticleSystemRenderSceneObject*) {}

	virtual void addTerrain(TerrainRenderSceneObject*) {}
	virtual void removeTerrain(TerrainRenderSceneObject*) {}

	virtual void addOcclusionArea(OcclusionArea* ) {}
	virtual void removeOcclusionArea(OcclusionArea* ) {}
	
	virtual void addOctreeNode(OctreeNode*, OctreeNode* parent=NULL) {}
	virtual void removeOctreeNode(OctreeNode*) {}

	virtual void addTest(TestRenderSceneObject* test) { tests.add(test); }
	virtual void removeTest(TestRenderSceneObject* test) { tests.remove(test); }
	virtual void getTests(DynamicArray<SharedPtr<TestRenderSceneObject>>& test_) { test_ = test_; }

};

RenderScene* CreateRenderScene();

#endif