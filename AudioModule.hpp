#pragma once

#ifndef __AM_HPP__
#define __AM_HPP__

/*
#include "Asset.hpp"
*/

#include "Module.hpp"


#include "AudioScene.hpp"





class AudioModule : public Module {


public:

	virtual void setVolume(float volume ) {}
	virtual void playSound(Sound*, float volume ) {}
	virtual void stopSound(Sound*, float volume ) {}


	/*
	virtual MaterialManager* getMaterialManager() const =0;
 	virtual TextureManager* getTextureManager() const =0;
	virtual MeshManager* getMeshManager() const =0;
	*/

	//virtual RenderScene* createScene() = 0;
	//virtual MaterialManager* getMaterialManager()=0; 



};


AudioModule* CreateAudioModule();




#endif