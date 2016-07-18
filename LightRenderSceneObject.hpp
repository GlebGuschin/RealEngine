#pragma once

#ifndef __LIGHT_RENDER_SCENE_OBJECT_HPP__
#define __LIGHT_RENDER_SCENE_OBJECT_HPP__

#include "RenderSceneObject.hpp"
#include "Texture.hpp"


enum LIGHT_TYPE { LIGHT_DIRECTIONAL, LIGHT_OMNI, LIGHT_SPOT };

enum LIGHT_COLOR_TYPE {
	LIGHT_COLOR_DIFFUSE = 0,
	LIGHT_COLOR_SPECULAR = 1,
	LIGHT_COLOR_AMBIENT = 2,
	LIGHT_COLOR_MAX
};


enum LIGHT_ATTENUATION_TYPE { 
	//LIGHT_ATTENUATION_
};
struct LightAttenuationInfo {
	float constant, linear, quadratic;	
};

struct LightInfo {
	Color colors[LIGHT_COLOR_MAX];
	//bool renderSprite;
	LightAttenuationInfo attenuation;
	LIGHT_TYPE type;
	float radius;
	float intensity;

	LightInfo() : type(LIGHT_DIRECTIONAL) {
		colors[LIGHT_COLOR_DIFFUSE] = Color(0.8, 0.8, 0.8);
		colors[LIGHT_COLOR_AMBIENT] = Color(0.2, 0.2, 0.2);
		colors[LIGHT_COLOR_SPECULAR] = Color(0.0, 0.0, 0.0);
	}

};



class LightRenderSceneObject : public RenderSceneObject {

	bool renderSprite;
	SharedPtr<Texture> cookie;

	LightInfo info;

public:

	LightRenderSceneObject()  { setRenderSprite(false); }


	LIGHT_TYPE getType() const { return info.type; }
	const LightInfo& getInfo() const { return info; }

	void setInfo(const LightInfo& info_) { info = info_; }

	void setRenderSprite(bool value) {}

	void setCookie(Texture*cookie_) { cookie = cookie_; }
	Texture* getCookie() const { return cookie; }

	void setColor(const Color& color, LIGHT_COLOR_TYPE type = LIGHT_COLOR_DIFFUSE) { info.colors[type] = color; }
	const Color& getColor(LIGHT_COLOR_TYPE type = LIGHT_COLOR_DIFFUSE) const { return info.colors[ type ];  }

	float getIntensity() const { return info.intensity; }
	void setIntensity(float intensity) { info.intensity = intensity; }


};




#endif