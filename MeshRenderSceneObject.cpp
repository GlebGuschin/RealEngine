#include "stdafx.h"
#include "MeshRenderSceneObject.hpp"



void MeshRenderSceneObject::setMesh(Mesh* mesh_) { 

	mesh = mesh_; 

}

Mesh* MeshRenderSceneObject::getMesh(Mesh* mesh_) const { 
	
	return mesh; 

}

void MeshRenderSceneObject::setMaterial(Material*, unsigned index) {

}

Material* MeshRenderSceneObject::getMaterial(unsigned index) const { 
	
	return NULL; 

}


void MeshRenderSceneObject::processPass(BaseRenderPassContext& rpc) {

	RenderSurface renderSurface;
	RenderObject renderObject;

	/*
	for (unsigned index = )
	renderSurface.setMaterial(getMaterial() )
	renderObject.
	*/

	rpc.addRenderObject(renderObject);
	
}
	
void MeshRenderSceneObject::processPass(ShadowRenderPassContext&) {
}

void MeshRenderSceneObject::processPass(TranslucentRenderPassContext&) {
}



