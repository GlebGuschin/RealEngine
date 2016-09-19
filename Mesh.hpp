#pragma once

#ifndef __MESH_HPP__
#define __MESH_HPP__


//#include "Common.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "Asset.hpp"
#include "Skeleton.hpp"

struct MeshLodValue {

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

class MeshLevelOfDetail : public Referenced {

};

class MeshLOD : public Referenced {

	DynamicArray<MeshItem> items;

public:

	unsigned getNumItems() { return (unsigned)items.size(); }

	void addItem(const MeshItem& item) { items.add(item); }
	void removeItem(unsigned itemIndex) { items.removeAt(itemIndex); }
	const MeshItem& getItem(unsigned itemIndex) const { return items[itemIndex]; }
	MeshItem& getItem(unsigned itemIndex) { return items[itemIndex]; }


};

class MeshAsset : public Asset {

	//TextureInfo info;
	//ResourceName;
	SharedPtr<Skeleton> skeleton;

	DynamicArray<SharedPtr<MeshLevelOfDetail>> meshLevelOfDetail;

public:

	void reload() {}

	Skeleton* getSkeleton() const { return skeleton; }
	void setSkeleton(Skeleton* skeleton_) { skeleton = skeleton_; }

	unsigned getNumMeshLevelOfDetail() const { return meshLevelOfDetail.size(); }
	MeshLevelOfDetail* getMeshLevelOfDetail(unsigned index = 0)  const { return meshLevelOfDetail[index]; }
	void addMeshLevelOfDetail(MeshLevelOfDetail* ) {  }
	void removeMeshLevelOfDetail(MeshLevelOfDetail*) {  }
	void clearMeshLevelOfDetail() {  }


};


class Mesh : public Referenced {
	
	SharedPtr<MeshAsset> asset;

	//DynamicArray<SharedPtr<MeshItem>> items;

	DynamicArray<SharedPtr<MeshLOD>> lods;
	SharedPtr<Skeleton> skeleton;

public:

	MeshAsset* getAsset() const { return asset; }

	virtual unsigned calcLOD(float distance) { return 0; }
	virtual unsigned getNumLOD() const { return (unsigned)lods.size(); }
	virtual MeshLOD* getMeshLOD(unsigned lodIndex) const { return lods[lodIndex]; }


	//virtual unsigned getNumItems(unsigned lod = 0) { return (unsigned)items.size(); }
	//virtual MeshItem* getItem(unsigned itemIndex, unsigned lod = 0) { return lods[lod]->getItem(itemIndex); }

	Skeleton* getSkeleton() const { return skeleton; }
	void setSkeleton(Skeleton*skeleton_) { skeleton = skeleton_; }
	
	virtual void setMaterial(Material* material, unsigned itemIndex, unsigned lodIndex =0)   {  /*items[itemIndex]->setMaterial(material); */ }
	virtual Material* getMaterial(unsigned  itemIndex, unsigned lodIndex = 0) const { return NULL; /* items[itemIndex]->getMaterial();*/ }
	//virtual void setGeometry(Geometry* geometry, unsigned itemIndex, unsigned lodIndex = 0) { /*items[itemIndex]->setGeometry(geometry); */ }
	//virtual Geometry* getGeometry(unsigned  itemIndex) { return items[itemIndex]->getGeometry(); }
	

};


#endif