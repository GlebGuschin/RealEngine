#pragma once

#ifndef __MESH_COMPONENT_HPP__
#define __MESH_COMPONENT_HPP__

#include "BaseComponent.hpp"
#include "RenderScene.hpp"

class MeshComponent : public BaseComponent {

	SharedPtr<MeshRenderSceneObject>   meshRenderSceneObject;

public:

	MeshComponent() : BaseComponent() {}
	~MeshComponent() {}

	virtual bool setMesh(const AssetName&) { return false; }
	void update(const TimeUpdate&) {}

	Material* getMaterial(unsigned index) const { return NULL; }


protected:

};


#endif