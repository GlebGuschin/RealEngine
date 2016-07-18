#pragma once

#ifndef __PS_RENDER_SCENE_OBJECT_HPP__
#define __PS_RENDER_SCENE_OBJECT_HPP__

#include "RenderSceneObject.hpp"
#include "ParticleSystem.hpp"


class ParticleSystemRenderSceneObject : public RenderSceneObject {

	SharedPtr<ParticleSystem> particleSystem;

public:

	ParticleSystemRenderSceneObject() {}	

	void setParticleSystem(ParticleSystem*particleSystem_) { particleSystem = particleSystem_; }
	ParticleSystem* getParticleSystem() const { return particleSystem; }


	void processPass(OpacityRenderPassContext&);
	void processPass(ShadowRenderPassContext&);
	void processPass(TranslucentRenderPassContext&);

};




#endif