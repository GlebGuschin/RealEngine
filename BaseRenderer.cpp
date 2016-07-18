#include "stdafx.h"
#include "BaseRenderer.hpp"


bool BaseRenderer::initialize(const RenderArea&) {

	return true;
}

void BaseRenderer::shutdown() {

}

/*
RenderScene* BaseRenderer::createScene() {

	return NULL;
}

void BaseRenderer::releaseScene(RenderScene*) {

}
*/

void BaseRenderer::beginFrame() {

	++statistic.currentFrame;

	for (size_t i = 0; i < listeners.size(); i++) {
			listeners[i]->onBeginFrame();
	}

}

void BaseRenderer::endFrame() {

	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->onEndFrame();
	}

}

void BaseRenderer::registerTexture(HardwareTexture* texture) {

	textures.add(texture);

}

void BaseRenderer::unregisterTexture(HardwareTexture*texture) {

	textures.remove(texture);

}

void BaseRenderer::registerScene(RenderScene* scene) {

	scenes.add(scene);

}

void BaseRenderer::unregisterScene(RenderScene* scene) {

	scenes.remove(scene);

}

RenderScene* BaseRenderer::createScene() {

	RenderScene* scene = CreateRenderScene();
	registerScene(scene);
	return scene;
}

void BaseRenderer::releaseScene(RenderScene* scene) {

	unregisterScene(scene);
}




HardwareTexture* BaseRenderer::createTexture(const HardwareTextureInfo&) {

	//te
	return NULL;
}

void BaseRenderer::releaseTexture(HardwareTexture*) {

}

HardwareVertexBuffer* BaseRenderer::createVertexBuffer(const HardwareVertexBufferInfo&) {
	return NULL;
}

HardwareIndexBuffer* BaseRenderer::createIndexBuffer(const HardwareIndexBufferInfo&) {
return NULL;
}
