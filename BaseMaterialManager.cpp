#include "stdafx.h"
#include "MaterialManager.hpp"
#include "TextureManager.hpp"


class BaseMaterialManager;

class BaseSurface : public Surface {

	SharedPtr<BaseMaterialManager> manager;

public:

	BaseSurface(BaseMaterialManager* manager_,  const SurfaceInfo& info) : Surface(info), manager(manager_) {}
	//BaseSurface(BaseMaterialManager* manager_, MaterialAsset* asset) : Material(asset), manager(manager_) {}
	//BaseSurface(BaseMaterialManager* manager_, const MaterialInfo& info, MaterialAsset* asset) : Material(info, asset), manager(manager_) {}
	
	~BaseSurface();

};


class BaseMaterial : public Material {

	SharedPtr<BaseMaterialManager> manager;

public:

	BaseMaterial(BaseMaterialManager* manager_,  const MaterialInfo& info) : Material(info), manager(manager_) {}
	BaseMaterial(BaseMaterialManager* manager_, MaterialAsset* asset) : Material(asset), manager(manager_) {}
	BaseMaterial(BaseMaterialManager* manager_, const MaterialInfo& info, MaterialAsset* asset) : Material(info, asset), manager(manager_) {}
	~BaseMaterial();

	Material* clone() const;
};


class BaseMaterialManager : public MaterialManager {

	DynamicArray<Material*> materials;
	SharedPtr<TextureManager> textureManager;
	DynamicArray<Surface*> surfaces;

protected:

public:

	Surface* createSurface(const SurfaceInfo&);
	Surface* createSurface(const AssetName&);
	void releaseSurface(Surface*);

	Material* createMaterial(const MaterialInfo&);
	Material* createMaterial(Material*);
	Material* createMaterial(const AssetName&);
	void releaseMaterial(Material*);
	Material* cloneMaterial(Material*);

};

SharedPtr<BaseMaterialManager> gMaterialManager;

Surface* BaseMaterialManager::createSurface(const SurfaceInfo&) {
	return NULL;
}

Surface* BaseMaterialManager::createSurface(const AssetName&) {
return NULL;
}

Material* BaseMaterialManager::createMaterial(const MaterialInfo& info) {

	BaseMaterial* material = new BaseMaterial(this, info);
	materials.add(material);

	return material;

}

Material* BaseMaterialManager::createMaterial(Material*) {
	Material* material = NULL;
	return material;

}

Material* BaseMaterialManager::createMaterial(const AssetName&) {
	Material* material = NULL;
	return material;

}

void BaseMaterialManager::releaseMaterial(Material* material) {

	materials.remove(material);
}

void BaseMaterialManager::releaseSurface(Surface* surface) {

	surfaces.remove(surface);
}


Material* BaseMaterialManager::cloneMaterial(Material* material) {
	
	BaseMaterial* material2 = new BaseMaterial(this, material->getInfo(), material->getAsset());

	for (unsigned i = 0; i < MATERIAL_TEXTURE_MAX; i++) {
		material2->setTexture(material->getTexture( (MATERIAL_TEXTURE_TYPE)i ) );
	}

	materials.add(material2);
	return material2;
}


BaseMaterial::~BaseMaterial() { 
	manager->releaseMaterial(this);	
}


Material* BaseMaterial::clone() const { 
	BaseMaterialManager* manager = (BaseMaterialManager*)this->manager;
	return manager->cloneMaterial((Material*)this);
}


BaseSurface::~BaseSurface() {

	manager->releaseSurface(this);

}


MaterialManager* GetMaterialManager() {

	if (!gMaterialManager) {
		gMaterialManager = new BaseMaterialManager;
	}

	MaterialManager* m = gMaterialManager;
	return m;
}
