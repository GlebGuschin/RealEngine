#pragma once

#ifndef __PX_SCENE_HPP__
#define __PX_SCENE_HPP__

//#include "DynamicArray.hpp"
//#include "AudioSceneObject.hpp"


Simulator


class AudioSceneListener : public Listener {

public:

};



class AudioScene : public AudioSceneObjectListener {

protected:

	DynamicArray<SharedPtr<AudioSceneObject>> sounds;

public:

	virtual void addListener(AudioSceneListener*) {}
	virtual void removeListener(AudioSceneListener*) {}

	virtual void addSound(AudioSceneObject* soundObject) {}
	virtual void removeSound(AudioSceneObject* soundObject) {}

	//virtual void setListener(const )

};

AudioScene* CreateAudioScene();

#endif