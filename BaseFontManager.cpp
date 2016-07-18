#include "stdafx.h"
#include "Font.hpp"


class BaseFont;

class BaseFontManager : public FontManager {

	DynamicArray<Font*> fonts;

	SharedPtr<Font> defaultFont;

public:

	Font* createFont(const AssetName&);

	Font* createFont(const FontInfo& info);
	void releaseFont(Font* font);	
	Font* getDefaultFont() const { return defaultFont; }

};

FontManager* CreateFontManager() { return new BaseFontManager; }


class BaseFont : public Font {

	SharedPtr<BaseFontManager> manager;

public:

	BaseFont(const FontInfo& info, BaseFontManager* manager_) : Font(info), manager(manager_) {}
	BaseFont(FontAsset* asset, BaseFontManager* manager_) : Font(asset), manager(manager_) {}
	
	FontManager* getManager() const { return manager; }

};

Font* BaseFontManager::createFont(const AssetName&) {

	FontAsset* asset = NULL;
	BaseFont* font = new BaseFont(asset,this);
	fonts.add(font);
	return font;

}

Font* BaseFontManager::createFont(const FontInfo& info) {

	BaseFont* font = new BaseFont(info, this);
	fonts.add(font);
	return font;

}

void BaseFontManager::releaseFont(Font* font) {

	fonts.remove(font);

}



