#pragma once

#ifndef __LIGHT_COMPONENT_HPP__
#define __LIGHT_COMPONENT_HPP__

#include "BaseComponent.hpp"


class LightComponent : public BaseComponent {

	SharedPtr<LightRenderSceneObject> light;
	
protected:

public:

	LightComponent() : BaseComponent() {}
	//BaseComponent(const Name& group_) : world(NULL), entity(NULL), group(group_){}
	~LightComponent() {}
	
	void update(const TimeUpdate&) {}	

protected:

	void onEnterWorld() {
		
		light = new LightRenderSceneObject();
		getWorld()->getRenderScene()->addLight(light);

	}

	void onLeaveWorld() {
	
	}

};


#endif