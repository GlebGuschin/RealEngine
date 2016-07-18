#include "stdafx.h"

#include "MeshRenderSceneObject.hpp"


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



