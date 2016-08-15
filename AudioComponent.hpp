#pragma once

#ifndef __AUDIO_COMPONENT_HPP__
#define __AUDIO_COMPONENT_HPP__

#include "BaseComponent.hpp"


class AudioComponent : public BaseComponent {

	//SharedPtr<LightRenderSceneObject> light;
	
protected:

public:

	AudioComponent() : BaseComponent() {}
	//BaseComponent(const Name& group_) : world(NULL), entity(NULL), group(group_){}
	~AudioComponent() {}
	
	void update(const TimeUpdate&) {}	

protected:

	void onEnterWorld() {
		
		//light = new LightRenderSceneObject();
		//getWorld()->getRenderScene()->addLight(light);

	}

	void onLeaveWorld() {
	
	}

};


#endif