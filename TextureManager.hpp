#pragma once

#ifndef __TEXTURE_MANAGER_HPP__
#define __TEXTURE_MANAGER_HPP__

#include "Texture.hpp"
#include "Renderer.hpp"

class TextureManager : public Referenced {

public:

	virtual Texture* createTexture(const AssetName&) = 0;
	virtual Texture* createTexture(const TextureInfo&) = 0;
	//virtual void releaseTexture(Texture*texture);

	virtual void getTextures( DynamicArray<SharedPtr<Texture>>& ) const =0;

};


//TextureManager* CreateTextureManager(Renderer* renderer);
	//TextureManager* CreateTextureManager();


#endif