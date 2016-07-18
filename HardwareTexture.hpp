#pragma once

#ifndef __HARDWARE_TEXTURE_HPP__
#define __HARDWARE_TEXTURE_HPP__

#include "RenderCommon.hpp"
#include "MemoryBuffer.hpp"


enum TEXTURE_TYPE { TEXTURE_2D, TEXTURE_2D_ARRAY, TEXTURE_3D, TEXTURE_CUBE, TEXTURE_TOTAL };


enum FACE_TYPE {
	FACE_PX = 0,
	FACE_NX = 1,
	FACE_PY = 2,
	FACE_NY = 3,
	FACE_PZ = 4,
	FACE_NZ = 5,
	FACE_TOTAL
};



enum TEXEL_FORMAT {

	TEXEL_NONE = 0,
	TEXEL_RGBA8 = 1,
	TEXEL_RGB8 = 2,

	

	TEXEL_DXT1 = 10,
	TEXEL_DXT3 = 13,
	TEXEL_DXT5 = 15,
	TEXEL_BC1 = 16,
	TEXEL_3DC = 17,

	TEXEL_RGBA16F = 20,
	TEXEL_RGBA32F = 21,

	TEXEL_D24S8 = 103

};

inline bool IsCompressedFormat(TEXEL_FORMAT type)  {
	return type == TEXEL_DXT1 || type == TEXEL_DXT3 || type == TEXEL_DXT5 || type == TEXEL_3DC;
}

size_t GetTextureSurfaceSize(TEXEL_FORMAT type, unsigned width, unsigned height);

class TextureSurface : public Referenced {
	
	SharedPtr<MemoryBuffer> buffer;
	unsigned width, height;
	TEXEL_FORMAT format;

public:

	TextureSurface( TEXEL_FORMAT format_, unsigned width_, unsigned height_, MemoryBuffer* buffer_ ) 
		: format(format_), width(width_), height(height_), buffer(buffer_) 
	{}

	MemoryBuffer* getBuffer() const { return buffer; }
	unsigned getWidth() const { return width; }
	unsigned getHeight() const { return height; }

};


class TextureVolume : public TextureSurface {

	unsigned depth;

public:

	TextureVolume( TEXEL_FORMAT format_, unsigned width_, unsigned height_, unsigned depth_, MemoryBuffer* buffer_ ) : 
	TextureSurface( format_, width_, height_, buffer_), depth( depth_) {}

	unsigned getDepth() const { return depth;}

};




struct CommonTextureInfo {
	TEXTURE_TYPE type;
	TEXEL_FORMAT format;
	unsigned width, height, depth, mipLevels;
	CommonTextureInfo() : type(TEXTURE_2D), width(1), height(1), depth(1) {}
};



struct HardwareTextureInfo : CommonTextureInfo {
	bool renderTarger;
	bool autoGenerateMipmaps;
	unsigned flags;
	//unsigned width, height, depth;
	unsigned mipLevels;
	float mipBias;
	//TEXTURE_TYPE type;
	
	HardwareTextureInfo() {}
};

struct HardwareTextureUpdateInfo {	

	unsigned x, y, z;
	unsigned width, height, depth;
	unsigned mipLevel;
	FACE_TYPE face;
	
	HardwareTextureUpdateInfo() {}	
};


class HardwareTexture : public Referenced {

	HardwareTextureInfo info;

public:

	HardwareTexture(const HardwareTextureInfo& info_) : info(info_) {}
	
	const HardwareTextureInfo& getInfo() const { return info; }

	virtual void generateMipmaps() {}

	virtual void update(unsigned mipLevel, TextureSurface*) {}
	virtual void update(FACE_TYPE faceType, unsigned mipLevel, TextureSurface*) {}
	virtual void update(unsigned mipLevel, unsigned layer, TextureSurface*) {}
	virtual void update(unsigned mipLevel, TextureVolume*) {}

};



#endif