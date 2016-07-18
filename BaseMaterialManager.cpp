#include "stdafx.h"
#include "MaterialManager.hpp"
#include "TextureManager.hpp"


class BaseMaterialManager;

class BaseMaterial : public Material {

	SharedPtr<BaseMaterialManager> manager;

public:

	BaseMaterial(BaseMaterialManager* manager_,  const MaterialInfo& info) : Material(info), manager(manager_) {}
	BaseMaterial(BaseMaterialManager* manager_, MaterialAsset* asset) : Material(asset), manager(manager_) {}
	BaseMaterial(BaseMaterialManager* manager_, const MaterialInfo& info, MaterialAsset* asset) : Material(info, asset), manager(manager_) {}

	Material* clone() const;
};


class BaseMaterialManager : public MaterialManager {

	DynamicArray<Material*> materials;
	SharedPtr<TextureManager> textureManager;

protected:

public:

	Material* createMaterial(const MaterialInfo&);
	Material* createMaterial(Material*);
	Material* createMaterial(const AssetName&);
	void releaseMaterial(Material*);
	Material* cloneMaterial(Material*);

};

SharedPtr<BaseMaterialManager> gMaterialManager;

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

Material* BaseMaterialManager::cloneMaterial(Material* material) {
	
	BaseMaterial* material2 = new BaseMaterial(this, material->getInfo(), material->getAsset());

	for (unsigned i = 0; i < MATERIAL_TEXTURE_MAX; i++) {
		material2->setTexture(material->getTexture( (MATERIAL_TEXTURE_TYPE)i ) );
	}

	materials.add(material2);
	return material2;
}


Material* BaseMaterial::clone() const { 
	BaseMaterialManager* manager = (BaseMaterialManager*)this->manager;
	return manager->cloneMaterial((Material*)this);
}

MaterialManager* GetMaterialManager() {

	if (!gMaterialManager) {
		gMaterialManager = new BaseMaterialManager;
	}

	MaterialManager* m = gMaterialManager;
	return m;
}
