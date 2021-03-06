#pragma once

#ifndef __MESH_RENDER_SCENE_OBJECT_HPP__
#define __MESH_RENDER_SCENE_OBJECT_HPP__

#include "RenderSceneObject.hpp"
#include "Mesh.hpp"


class MeshRenderSceneObject : public RenderSceneObject {

	SharedPtr<Mesh> mesh;

public:

	MeshRenderSceneObject() {}	

	virtual void setMesh(Mesh* mesh_);
	virtual Mesh* getMesh(Mesh* mesh_) const;

	virtual void setMaterial(Material*, unsigned index);
	virtual Material* getMaterial(unsigned index) const;


	void processPass(BaseRenderPassContext&);
	void processPass(ShadowRenderPassContext&);
	void processPass(TranslucentRenderPassContext&);

};

#endif