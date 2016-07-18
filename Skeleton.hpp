#pragma once

#ifndef __SKELETON_HPP__
#define __SKELETON_HPP__


//#include "Common.hpp"
#include "Name.hpp"
#include "Transform.hpp"
#include "Asset.hpp"


#define MAX_BONES 255

class Bone : public Referenced {	

	Name name;
	Transform transform;

	SharedPtr<Bone> parent;
	DynamicArray<SharedPtr<Bone>> children;

public:

	Bone(const Name& name_) : name(name_) {}

	const Name& getName() const { return name; }

	void addChild(Bone* child) { children.add(child); child->setParent(this); }
	void removeChild(Bone* child) { children.remove(child); }

	void setParent(Bone* parent_) { parent = parent_; }

	void dump(unsigned offset = 0) {
	
		std::string string;
		//string.resize(offset);
		for (unsigned i = 0; i < offset; i++) string += ' ';
		OutputDebugStringA(string.c_str());
		OutputDebugStringA(name);
		OutputDebugStringA("\n");

		offset += 1;

		for (size_t i = 0; i < children.size(); i++) {
			children[i]->dump(offset);
		}

	
	}
		
};

#define BONE_INDEX_NONE (unsigned)-1

class Skeleton : public Referenced {

	SharedPtr<Bone> root;
	
	DynamicArray<SharedPtr<Bone>> bones;

public:

	Skeleton()  { 

		root = new Bone("Root");
		bones.add(root);
	}

	~Skeleton() { 

		for (size_t i = 0; i < bones.size(); i++) {
			bones[i]->setParent(NULL);			
		}

		bones.clear();
		root = NULL;
	}

	//MeshAsset* getAsset() const { return asset; }

	Bone* getRoot() const { return root; }
	unsigned getNumBones() const { return (unsigned)bones.size();  }

	void addBone(Bone* bone, Bone* parent = NULL) {

		assert(bone);

		if (parent == NULL) {
			parent = root;
		}

		if (!findBone(bone->getName())) {
				parent->addChild(bone);
				bones.add(bone);
		}

	}

	void removeBone(Bone* bone, Bone* parent = NULL);

	Bone* findBone(const Name& name) const {
	
		for (size_t i = 0; i < bones.size(); i++) {
			Bone* bone = bones[i];
			if (bone->getName() == name) return bone;
		}

		return NULL;
	}

	unsigned findBoneIndex(const Name& name) const {

		for (size_t i = 0; i < bones.size(); i++) {
			Bone* bone = bones[i];
			if (bone->getName() == name) return (unsigned)i;
		}

		return BONE_INDEX_NONE;
	}

	
	void dump() {

		getRoot()->dump();
	}


	
};


#endif