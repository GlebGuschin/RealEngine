#pragma once

#ifndef __PHYSICAL_SCENE_HPP__
#define __PHYSICAL_SCENE_HPP__

//#include "DynamicArray.hpp"
//#include "AudioSceneObject.hpp"


//Simulator Physical


class PhysicalSceneListener : public Listener {

public:

};



class PhysicalScene : public PhysicalSceneObjectListener {

protected:

	//DynamicArray<SharedPtr<AudioSceneObject>> sounds;

public:

	/*
	virtual void addListener(AudioSceneListener*) {}
	virtual void removeListener(AudioSceneListener*) {}

	virtual void addSound(AudioSceneObject* soundObject) {}
	virtual void removeSound(AudioSceneObject* soundObject) {}

	//virtual void setListener(const )
	*/

};

AudioScene* CreateAudioScene();

#endif