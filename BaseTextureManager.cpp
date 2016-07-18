#include "stdafx.h"
#include "TextureManager.hpp"
#include "TextureFile.hpp"


#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
                ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) |   \
                ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))

#pragma pack (push, 1)
struct DDSPixelformat
{
	unsigned long dwSize;
	unsigned long dwFlags;
	unsigned long dwFourCC;
	unsigned long dwRGBBitCount;
	unsigned long dwRBitMask;
	unsigned long dwGBitMask;
	unsigned long dwBBitMask;
	unsigned long dwABitMask;
};

struct DDSHeader {

	unsigned long dwMagic;
	unsigned long dwSize;
	unsigned long dwFlags;
	unsigned long dwHeight;
	unsigned long dwWidth;
	unsigned long dwPitchOrLinearSize;
	unsigned long dwDepth;
	unsigned long dwMipMapCount;
	unsigned long dwReserved1[11];
	DDSPixelformat ddspf;
	unsigned long dwCaps1;
	unsigned long dwCaps2;
	unsigned long dwReserved2[3];
};

struct DDS_HEADER_DXT10 {
	unsigned long dxgiFormat;
	unsigned long	resourceDimension;
	unsigned long miscFlag;
	unsigned long arraySize;
	unsigned long miscFlags2;
} ;

#pragma pack (pop)




void TextureAsset::load() {

	Asset::load();

	int i = 0;

	MemoryBuffer* memoryBuffer = getBuffer();

	char* ptr = (char*)memoryBuffer->lock();

	DDSHeader* ddsHeader = (DDSHeader*)ptr;

	info.width = ddsHeader->dwWidth;
	info.height = ddsHeader->dwHeight;
	info.mipLevels = ddsHeader->dwMipMapCount;
	
	size_t contentOffset = sizeof(DDSHeader);

	const DWORD dxt1 = MAKEFOURCC('D','X','T','1');
	const DWORD dxt5 = MAKEFOURCC('D','X','T','5');
	const DWORD dx10 = MAKEFOURCC('D','X','1','0');
	const DWORD atn2 = MAKEFOURCC('A','T','N','2');

	TEXEL_FORMAT texelFormat = TEXEL_NONE;
	switch (ddsHeader->ddspf.dwFourCC) {

		case dxt1:
			texelFormat = TEXEL_DXT1;
			break;

		case dxt5:
			texelFormat = TEXEL_DXT5;
			break;

		case atn2:
			texelFormat = TEXEL_3DC;
			break;

		case dx10:
			{
				contentOffset += sizeof(DDS_HEADER_DXT10);
				//ptr += sizeof(DDS_HEADER_DXT10);
				DDS_HEADER_DXT10* ddsHeaderDX10 = (DDS_HEADER_DXT10*)&ptr[sizeof(DDSHeader)];
				switch (ddsHeaderDX10->dxgiFormat) {				
					case 71:
						texelFormat = TEXEL_DXT1;
						break;
					case 83:
						texelFormat = TEXEL_3DC;
						break;
				};

				if( ddsHeaderDX10->resourceDimension == 3 ) {
						info.type = TEXTURE_2D_ARRAY;
						info.depth = ddsHeaderDX10->arraySize;
				}

			}

			break;
	
	};

	unsigned width = info.width;
	unsigned height = info.height;
	unsigned mipLevels = info.mipLevels ? info.mipLevels : 1;

	size_t contentSize = 0;
	for (unsigned mipLevel = 0; mipLevel < mipLevels; mipLevel++) {

			if (IsCompressedFormat(texelFormat) && (width < 4 || height < 4)) continue;
			contentSize += GetTextureSurfaceSize(texelFormat, width, height);
			
			width >>= 1;
			height >>= 1;
	}

	size_t memoryBufferSize = memoryBuffer->getSize();
	const size_t DDSHeaderSize = sizeof(DDSHeader);
	contentSize += DDSHeaderSize;

	memoryBuffer->unlock();

}

void TextureAsset::reload() {

}

void TextureAsset::unload() {

}





class BaseTextureManager;

class BaseTexture : public Texture {

	SharedPtr<BaseTextureManager> manager;

public:

	BaseTexture(BaseTextureManager* manager_,  const TextureInfo& info ) : Texture(info), manager(manager_) {}
	BaseTexture(BaseTextureManager* manager_, TextureAsset* asset) : Texture(asset), manager(manager_) {}
	~BaseTexture();
 
	TextureManager* getManager() const { 
		BaseTextureManager* manager = this->manager;
		return (TextureManager*)manager; 
	}
	
	void update();

};

class BaseTextureManager : public TextureManager {


	DynamicArray<BaseTexture*> textures;

	void releaseTexture(BaseTexture*);
	void addTexture(BaseTexture*);

public:

	Texture* createTexture(const AssetName&) { 


		return NULL;  
	}

	Texture* createTexture(const TextureInfo& info) { 

		BaseTexture* texture = new BaseTexture(this, info);
		addTexture(texture);

		return texture;

	}

	friend class BaseTexture;

};



void BaseTexture::update() {

	//TextureFile* tf=NULL;
	TextureAsset* asset = getAsset();

	HardwareTexture* htexture=NULL;

	//TEXTURE_2D, TEXTURE_2D_ARRAY, TEXTURE_3D, TEXTURE_CUBE

	switch(getInfo().type) {

		case TEXTURE_2D:	
			for(unsigned mipLevel = 0; mipLevel < asset->getMipLevels(); mipLevel++) {
				htexture->update(mipLevel, asset->getVolume(mipLevel) );
			}
			break;

		case TEXTURE_3D:	
			for(unsigned mipLevel = 0; mipLevel < asset->getMipLevels(); mipLevel++) {
				htexture->update(mipLevel, asset->getVolume(mipLevel));
			}
			break;
	
		case TEXTURE_CUBE:
			for(unsigned face = 0; face < 6; face++) {		
				for(unsigned mipLevel = 0; mipLevel < asset->getMipLevels(); mipLevel++) {					 
						htexture->update( (FACE_TYPE)face, mipLevel, asset->getSurface( (FACE_TYPE)face, mipLevel ) );
				}
			}
			break;
	
		case TEXTURE_2D_ARRAY:
			for(unsigned layer = 0; layer < asset->getDepth(); layer++) {		
				for(unsigned mipLevel = 0; mipLevel < asset->getMipLevels(); mipLevel++) {					 
						htexture->update( layer, mipLevel, asset->getSurface( layer, mipLevel ) );
				}
			}

	};

}


BaseTexture::~BaseTexture() {
	manager->releaseTexture(this);
}

void BaseTextureManager::addTexture(BaseTexture* texture) {

	textures.add( texture );

}

void BaseTextureManager::releaseTexture(BaseTexture* texture) {

	int i = 0;
	textures.remove(texture);

}

TextureManager* CreateTextureManager() { return new BaseTextureManager; }




