#include "stdafx.h"
#include "SoundManager.hpp"

class BaseSoundManager : public SoundManager {

	DynamicArray<Sound*> sounds;

public:

	Sound* createSound(const AssetName& name) { 

		SoundAsset* asset = new SoundAsset(name);
		asset->load();

		Sound* sound = new Sound( asset );
		sounds.add(sound);
		return sound; 
	}

	void releaseSound(Sound* sound)  {
	
		sounds.remove(sound);
	
	}
	
};

SoundManager* CreateSoundManager() { return new BaseSoundManager; }

