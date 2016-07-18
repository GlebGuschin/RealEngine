#include "stdafx.h"
#include "BaseRenderScene.hpp"

/*
class BaseRenderScene : public RenderScene {

protected:

	//void addRenderComponent(RenderComponent*) {}
	//void removeRenderComponent(RenderComponent*) {}

	void onChangedTransform(RenderSceneObject*) {

		printf("");

	}

public:

	virtual void addListener(RenderSceneListener*) {}
	virtual void removeListener(RenderSceneListener*) {}

	//size_t getNumRenderObjects() const { return objects; }
	//const DynamicArray<SharedPtr<RenderSceneObject>>& getSceneObjects() const { return objects; }
	
	void addSceneObject(RenderSceneObject* object) { 
		objects.add(object); 
		object->addListener(this);
	}

	void removeSceneObject(RenderSceneObject* object) { 
		object->removeListener(this);
		objects.remove(object); 
	}

};
*/

void BaseRenderScene::addLight(LightRenderSceneObject* light) {

	if (light->getType() == LIGHT_DIRECTIONAL) {
			sunLight = light;
	} else {
			
	}	

	lights.add(light);

}

void BaseRenderScene::removeLight(LightRenderSceneObject*  light) {

	if (light == sunLight) {
			sunLight = light;
	}
	else {
	
	}

	lights.remove( light);

}


void BaseRenderScene::addMesh(MeshRenderSceneObject* mesh) {
	meshes.add(mesh);
}

void BaseRenderScene::removeMesh(MeshRenderSceneObject* mesh) {
	meshes.remove(mesh);
}

void BaseRenderScene::addParticleSystem(ParticleSystemRenderSceneObject*) {

}

void BaseRenderScene::removeParticleSystem(ParticleSystemRenderSceneObject*) {

}


void BaseRenderScene::addOcclusionArea(OcclusionArea* area) {
	occlusionAreas.add(area);
}

void BaseRenderScene::removeOcclusionArea(OcclusionArea* area) {
	occlusionAreas.remove(area);
}

void BaseRenderScene::getMeshes(DynamicArray<SharedPtr<MeshRenderSceneObject>>& meshes_) { 
	meshes_ =  meshes;
}
void BaseRenderScene::getLights(DynamicArray<SharedPtr<LightRenderSceneObject>>& lights_ )  {
	lights_ = lights;
}

void BaseRenderScene::getParticleSystems(DynamicArray<SharedPtr<ParticleSystemRenderSceneObject>>&) {

}


void BaseRenderScene::getOcclusionAreas(DynamicArray<SharedPtr<OcclusionArea>>& occlusionAreas_) {
	occlusionAreas_ = occlusionAreas;
}


RenderScene* CreateRenderScene() { return new BaseRenderScene; }

