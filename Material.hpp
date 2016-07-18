#pragma once

#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

//#include "RenderComponent.hpp"
#include "Referenced.hpp"
#include "Texture.hpp"
#include "Asset.hpp"


class MaterialManager;

struct SurfaceInfo { 
	float reverbation;
	float friction;
	float buoyancy;
};



class Surface : public Referenced {

	SurfaceInfo info;

public:

	Surface() {}
	Surface(const SurfaceInfo& info_) : info(info_) { }

};




struct MaterialTextureTranform {
	float a;
};

enum MATERIAL_COLOR_TYPE {
	MATERIAL_COLOR_DIFFUSE =0,
	MATERIAL_COLOR_SPECULAR,
	MATERIAL_COLOR_EMISSION,
	MATERIAL_COLOR_MAX
};

enum MATERIAL_BLEND_TYPE {
	MATERIAL_BLEND_NONE = 0,	
	MATERIAL_BLEND_MASKED,
	MATERIAL_BLEND_ADDITIVE,	
	MATERIAL_BLEND_TRANSLUCENT
};

enum MATERIAL_TEXTURE_TYPE {
	MATERIAL_TEXTURE_DEFAULT = 0,	
	MATERIAL_TEXTURE_DEFFUSE = MATERIAL_TEXTURE_DEFAULT,	
	MATERIAL_TEXTURE_NORMAL,
	MATERIAL_TEXTURE_SPECULAR,
	MATERIAL_TEXTURE_EMISSION,
	MATERIAL_TEXTURE_DETAIL,
	MATERIAL_TEXTURE_NORMAL_DETAIL,
	MATERIAL_TEXTURE_ENV,
	MATERIAL_TEXTURE_MAX
};

enum MATERIAL_SUFRACE_TYPE {
	MATERIAL_SUFRACE_DEFAULT = 0,	
	MATERIAL_SUFRACE_MAX
};

enum MATERIAL_SHADE_TYPE {
	MATERIAL_SHADE_UNLIT = 0,
	MATERIAL_SHADE_DEFAULT = 1,
	MATERIAL_SHADE_FOLIAGE = 2
};

struct MaterialInfo {
	Color colors[MATERIAL_COLOR_MAX];
	bool twoSide;
	bool refraction;
	float opacity;
	float alphaRef;
	bool SmartPtrraction;
	MATERIAL_SHADE_TYPE shadeType;
	MATERIAL_BLEND_TYPE blendType;
	MaterialInfo() : twoSide(false), opacity(1.0f), shadeType(MATERIAL_SHADE_UNLIT), blendType(MATERIAL_BLEND_NONE) {}


	bool isEqual(const MaterialInfo& other) const {

		for (unsigned i = 0; i < MATERIAL_COLOR_MAX; i++) {
			if (colors[i] != other.colors[i]) return false;
		}
		if (twoSide != other.twoSide) return false;
		return true;
	}

	bool operator==(const MaterialInfo& other) const { 
		return true;
	}


};

class MaterialLayer : public Referenced {

	//MaterialInfo info;
	SharedPtr<Texture> textures[MATERIAL_TEXTURE_MAX];	

public:

	virtual Texture* getTexture(MATERIAL_TEXTURE_TYPE type = MATERIAL_TEXTURE_DEFAULT) const { return NULL; }
	virtual void setTexture(Texture* texture, MATERIAL_TEXTURE_TYPE type = MATERIAL_TEXTURE_DEFAULT) {}

};



class MaterialAsset : public Asset {

public:

};

class Material : public Referenced {

	MaterialInfo info;
	SharedPtr<Texture> textures[MATERIAL_TEXTURE_MAX];

	SharedPtr<MaterialAsset> asset;

	//DynamicArray<SharedPtr<MaterialLayer>> layers;

public:


	Material(const MaterialInfo& info_) : info(info_) {}
	Material(MaterialAsset* asset_) : asset(asset_) {}
	Material(const MaterialInfo& info_, MaterialAsset* asset_) : asset(asset_), info(info_) {}

	void setOpacity(float alpha) { info.opacity = alpha; }
	float getOpacity() const { return info.opacity; }
	bool isOpacity() const { return info.opacity >= 1.0f; }
	bool isRenderRelevance(const Material*) const { return false; }
	bool isRefraction() const { return info.refraction; }
	bool isReflection() const { return info.refraction; }

	const MaterialInfo& getInfo() const { return info; }
	MaterialAsset* getAsset() const { return asset; }
	MaterialManager* getManager() const { return NULL; }

	//unsigned getNumLayers() const { return (unsigned)layers.size(); }

	Texture* getTexture(MATERIAL_TEXTURE_TYPE type = MATERIAL_TEXTURE_DEFAULT, unsigned layer = 0) const { 

		//MaterialLayer* l = layers[ layer ];
		//Texture* texture = l->getTexture(type);
		Texture* texture = textures[type];

		return texture; 
	}

	void setTexture(Texture* texture, MATERIAL_TEXTURE_TYPE type = MATERIAL_TEXTURE_DEFAULT, unsigned layer = 0) {
		//layers[ layer ]->setTexture( texture, type);
		textures[type] = texture;
	} 

	const Color& getColor(MATERIAL_COLOR_TYPE type = MATERIAL_COLOR_DIFFUSE) const { return info.colors[ type ]; }
	void setColor(const Color& color, MATERIAL_COLOR_TYPE type= MATERIAL_COLOR_DIFFUSE) { info.colors[ type ] = color; }


	virtual Material* clone() const { return NULL; }

};

const Name& GetName( MATERIAL_TEXTURE_TYPE type);



#endif