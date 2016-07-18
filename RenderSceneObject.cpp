#include "stdafx.h"
#include "RenderSceneObject.hpp"



//virtual void addListener(RenderSceneObjectListener* listener) { listeners.add(listener); }
//virtual void removeListener(RenderSceneObjectListener* listener) { listeners.remove(listener);}

void RenderSceneObject::processPass(OpacityRenderPassContext&) {}
void RenderSceneObject::processPass(BaseRenderPassContext&) {}
void RenderSceneObject::processPass(ShadowRenderPassContext&) {}
void RenderSceneObject::processPass(TranslucentRenderPassContext&) {}





void TestRenderSceneObject::processPass(OpacityRenderPassContext&) {

}

void TestRenderSceneObject::processPass(BaseRenderPassContext& context) {

	RenderObject renderObject;
	for (unsigned i = 0; i < items.size(); i++) {
			if (items[i].material->isOpacity()) {				
				//RenderSurface renderSurface;
				renderObject.setSurface(RenderSurface(items[i].geometry, items[i].material));
				context.addRenderObject(renderObject);
			} else {
				renderObject.setSurface(RenderSurface(items[i].geometry, items[i].material));
				//context.addRenderObject(renderObject, items[i].material->isRefraction() );
			}	
	}

}

void TestRenderSceneObject::processPass(ShadowRenderPassContext& context) {

}

void TestRenderSceneObject::processPass(TranslucentRenderPassContext& context) {

}




