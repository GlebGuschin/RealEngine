#pragma once

#ifndef __SOUND_MANAGER_HPP__
#define __SOUND_MANAGER_HPP__

#include "Sound.hpp"

class SoundManager : public Referenced {

public:

	virtual Sound* createSound(const AssetName&) = 0;
	virtual void releaseSound(Sound*) = 0;
	
};

SoundManager* CreateSoundManager();


#endif