#pragma once

#ifndef __PS_COMPONENT_HPP__
#define __PS_COMPONENT_HPP__

#include "BaseComponent.hpp"
#include "RenderScene.hpp"

class ParticleSystemComponent : public BaseComponent {

	SharedPtr<ParticleSystemRenderSceneObject>   particleSystemRenderSceneObject;
	
public:

	ParticleSystemComponent() : BaseComponent() {}
	//ParticleSystemComponent(const Name& group_) : world(NULL), entity(NULL), group(group_){}
	~ParticleSystemComponent() {}


	bool setParticleSystem(const AssetName&) { return false; }
	
	void update(const TimeUpdate&) {}

	

protected:

};


#endif