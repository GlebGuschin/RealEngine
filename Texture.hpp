#pragma once

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__


//#include "Common.hpp"
#include "HardwareTexture.hpp"
#include "Color.hpp"
#include "Asset.hpp"


class Texture;
class TextureManager;

struct TextureInfo : CommonTextureInfo {
	//TEXTURE_TYPE type;
	//unsigned width, height, depth;
	bool streamable;
	TextureInfo() : CommonTextureInfo(), streamable(false){}
};


class TextureAsset : public Asset {

	TextureInfo info;
	
public:

	unsigned getWidth( uint mipLevel = 0 ) const { return( 0 ); }
	unsigned getHeight( uint mipLevel = 0 ) const { return( 0 ); }
	unsigned getDepth( uint mipLevel = 0 ) const { return( 0 ); }
	unsigned getMipLevels() const { return( 0 ); }
	
	TextureSurface* getSurface(FACE_TYPE type, unsigned mipLevel) const { return NULL; }
	TextureSurface* getSurface(unsigned layer, unsigned mipLevel) const { return NULL; };
	TextureSurface* getSurface(unsigned mipLevel) const { return NULL; };
	TextureVolume* getVolume(unsigned mipLevel) const { return NULL; };

	void load();
	void reload();
	void unload();
	

	TextureAsset(const AssetName& name) : Asset(name) {}
	
};

enum HARDWARE_TEXTURE_TYPE {
	HARDWARE_TEXTURE_DEFAULT = 0,
	HARDWARE_TEXTURE_PROXY,
	HARDWARE_TEXTURE_ARRAY,
	HARDWARE_TEXTURE_MAX 
};

class Texture : public Referenced {

	TextureInfo info;
	SharedPtr<TextureAsset> asset;
	SharedPtr<HardwareTexture> htextures[HARDWARE_TEXTURE_MAX];

	unsigned useCounter;

public:

	Texture(const TextureInfo& info_) : info(info_), useCounter(0) {}
	Texture(TextureAsset* asset_) : asset(asset_), useCounter(0) {}


	virtual TextureManager* getManager() const { return NULL; }
	TextureAsset* getAsset() const { return asset; }

	HardwareTexture* getHardwareTexture(HARDWARE_TEXTURE_TYPE type = HARDWARE_TEXTURE_DEFAULT) const { return htextures[ type ]; }

	const TextureInfo& getInfo() const { return info; };

	bool isStreamable() const { return info.streamable; }

	void incUseCounter() { useCounter++; }
	void clearUseCounter() { useCounter = 0; }
	unsigned getUseCounter() const { return useCounter; }

	virtual void update() {}

};



#endif