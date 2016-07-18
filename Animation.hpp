#pragma once

#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include "RenderCommon.hpp"
//#include "HardwareVertexBuffer.hpp"
//#include "HardwareIndexBuffer.hpp"
#include "Skeleton.hpp"


class MatrixPalette : public Referenced {

	Matrix4x4 palette[MAX_BONES];

public:

	const Matrix4x4& getMatrix(unsigned index) const { return palette[index]; }

};

struct AnimationTrackInfo {
	float duration;
	float fps;
};


class AnimationTrackAsset : public Asset {

public:

	AnimationTrackAsset(const AssetName& assetName) : Asset(assetName) {}

	void load() {}
	void unload() {}
	void reload() {}

};

enum ANIMATION_PLAY_TYPE {
	ANIMATION_PLAY_SINGLE = 0,
	ANIMATION_PLAY_LOOP = 1,
	//ANIMATION_PLAY_LOOP = 1,
};

class AnimationTrack : public Referenced {

	SharedPtr<AnimationTrackAsset> asset;

public:

	AnimationTrackAsset* getAsset() const { return asset; }

	float getDuration() const { return 1.0f; }
	bool getAnimation(float time, Transform&) {
		return true; 
	}
	//AnimationTrack(const Name& name) {}
	//const Matrix4x4& getMatrix(unsigned index) const { return palette[index]; }

};



#endif

