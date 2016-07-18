#include "stdafx.h"
#include  "SoundManager.hpp"


void AudioTest1() {

	return;

	SoundManager* soundManager = CreateSoundManager();

	for(int i = 0; i < 100000; i++ )
	SharedPtr<Sound> sound = soundManager->createSound("content/ptrs.wav");



	//sound->removeSmartPtr
}

