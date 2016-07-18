#pragma once

#ifndef __MESH_HPP__
#define __MESH_HPP__


//#include "Common.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "Asset.hpp"

struct LodValue {

	float distance;
};


class MeshItem {

	SharedPtr<Geometry> geometry;
	SharedPtr<Material> material;

public:
	 
	void setMaterial(Material*material_) { material = material_; }
	Material* getMaterial() const { return material; }

	void setGeometry(Geometry* geometry_) { geometry = geometry_; }
	Geometry* getGeometry() const { return geometry; }

	bool operator==(const MeshItem& other) const { return geometry == other.geometry && material == other.material; }

};


class MeshLOD : public Referenced {

	DynamicArray<MeshItem> items;

public:

	unsigned getNumItems() { return (unsigned)items.size(); }

	void addItem(const MeshItem& item) { items.add(item); }
	void removeItem(unsigned itemIndex) { items.removeAt(itemIndex); }
	const MeshItem& getItem(unsigned itemIndex) const { return items[itemIndex]; }
	MeshItem& getItem(unsigned itemIndex) { return items[itemIndex]; }


	//static 

};

class MeshAsset : public Asset {

	//TextureInfo info;
	//ResourceName;

public:

	void reload() {}

};


class Mesh : public Referenced {
	
	SharedPtr<MeshAsset> asset;

	//DynamicArray<SharedPtr<MeshItem>> items;

	DynamicArray<SharedPtr<MeshLOD>> lods;

public:

	MeshAsset* getAsset() const { return asset; }

	virtual unsigned calcLOD(float distance) { return 0; }
	virtual unsigned getNumLOD() const { return (unsigned)lods.size(); }
	virtual MeshLOD* getMeshLOD(unsigned lodIndex) const { return lods[lodIndex]; }


	//virtual unsigned getNumItems(unsigned lod = 0) { return (unsigned)items.size(); }
	//virtual MeshItem* getItem(unsigned itemIndex, unsigned lod = 0) { return lods[lod]->getItem(itemIndex); }

	
	virtual void setMaterial(Material* material, unsigned itemIndex, unsigned lodIndex =0)   {  /*items[itemIndex]->setMaterial(material); */ }
	virtual Material* getMaterial(unsigned  itemIndex, unsigned lodIndex = 0) const { return NULL; /* items[itemIndex]->getMaterial();*/ }
	//virtual void setGeometry(Geometry* geometry, unsigned itemIndex, unsigned lodIndex = 0) { /*items[itemIndex]->setGeometry(geometry); */ }
	//virtual Geometry* getGeometry(unsigned  itemIndex) { return items[itemIndex]->getGeometry(); }
	

};


#endif