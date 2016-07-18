#pragma once

#ifndef __MATERIAL_MANAGER_HPP__
#define __MATERIAL_MANAGER_HPP__


#include "Material.hpp"
#include "TextureManager.hpp"

class MaterialManager : public Referenced {
	
public:

	//virtual Surface* createSurface(const SurfaceInfo&) = 0;

	virtual Material* createMaterial(const MaterialInfo&) = 0;
	virtual Material* createMaterial(Material*) = 0;
	virtual Material* createMaterial(const AssetName&) = 0;
	virtual void releaseMaterial(Material*) = 0;
	virtual Material* cloneMaterial(Material*) = 0;


};

MaterialManager* CreateMaterialManager();
MaterialManager* GetMaterialManager();

#endif