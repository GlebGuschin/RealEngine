#pragma once

#ifndef __HARDWARE_SOUND_HPP__
#define __HARDWARE_SOUND_HPP__


#include "Referenced.hpp"

enum SOUND_TYPE {
	SOUND_MONO_8, 
	SOUND_STEREO_8,
};

struct HardwareSoundInfo {
	SOUND_TYPE type;
};


class HardwareSound : public Referenced {
	HardwareSoundInfo info;
public:
	HardwareSound(const HardwareSoundInfo& info_) : info(info_) {}
};




#endif