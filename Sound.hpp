#pragma once

#ifndef __SOUND_HPP__
#define __SOUND_HPP__


#include "Asset.hpp"
#include "HardwareSound.hpp"



struct SoundInfo {
	unsigned i;

};


class SoundAsset : public Asset {

	SoundInfo info;

public:

	SoundAsset(const AssetName& name ) : Asset(name) {}
	~SoundAsset() {}

	void load();
	void reload();
	void unload();
	
};

class Sound : public Referenced {

	SoundInfo info;
	SharedPtr<SoundAsset> asset;

public:

	Sound(const SoundInfo& info_ ) : info(info_) {}
	Sound(SoundAsset* asset_ ) : asset(asset_) {}

	virtual SoundAsset* getAsset() const { return asset; }

	HardwareSound* getSound() const {return NULL; }

};



#endif