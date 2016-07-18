#pragma once

#ifndef __AUDITOR_HPP__
#define __AUDITOR_HPP__


//#include "Common.hpp"
#include "Asset.hpp"
#include "AudioScene.hpp"


class Auditor : public Referenced {

public:

	virtual HardwareSound* createSound(const HardwareSoundInfo&) = 0;
	virtual void releaseSound(HardwareSound*) = 0;

	//virtual void playSound(HardwareSound*) = 0;
	virtual void playSound(Sound*, float volume) {}
	virtual void stopSound(Sound*, float volume) {}
	virtual void setVolume(float volume) {}

};


#endif