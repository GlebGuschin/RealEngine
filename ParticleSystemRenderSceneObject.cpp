#include "stdafx.h"
#include "ParticleSystemRenderSceneObject.hpp"


void ParticleSystemRenderSceneObject::processPass(OpacityRenderPassContext& context) {

	for (unsigned streamIndex = 0; streamIndex < particleSystem->getNumStreams(); streamIndex++) {
		Material* material = particleSystem->getStream(streamIndex)->getMaterial();	
	}

}

void ParticleSystemRenderSceneObject::processPass(ShadowRenderPassContext& context) {

}

void ParticleSystemRenderSceneObject::processPass(TranslucentRenderPassContext& context) {


}

