#pragma once

#ifndef __FONT_HPP__
#define __FONT_HPP__

#include "Common.hpp"
#include "Referenced.hpp"
#include "Texture.hpp"
#include "Asset.hpp"

class FontManager;

enum FONT_TYPE {
	FONT_DEFAULT = 0,
};

struct FontInfo {
	FONT_TYPE type;
	unsigned width, height;
};


class FontAsset : public Asset {

public:

	FontAsset() {}
	
};

 

class Font : public Referenced {

protected:

	FontInfo info;
	SharedPtr<FontAsset> asset;

public:

	Font(const FontInfo& info_) : info(info_) {}
	Font(FontAsset* asset_) : asset(asset_) {
		// info;
	}
	
	FontAsset* getAsset() const { return asset; }
	virtual Texture* getTexture() const { return NULL; }	
	virtual FontManager* getManager() const { return NULL; }

};

class FontManager : public Referenced {

public:

	virtual Font* createFont(const AssetName&) = 0;
	virtual Font* createFont(const FontInfo& )=0;
	virtual void releaseFont(Font*)=0;
	Font* getDefaultFont() const { return NULL; }

};




#endif