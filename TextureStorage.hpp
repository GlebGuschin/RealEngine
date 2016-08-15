#pragma once

#ifndef __TEXTURE_STORAGE_HPP__
#define __TEXTURE_STORAGER_HPP__

#include "HardwareTexture.hpp"


struct TextureMipLevel {
	unsigned width, height, depth;
	size_t offset;
	size_t size;
	TextureMipLevel() : width( 0 ), height( 0 ), depth( 0 ), offset( 0 ), size( 0 ) {}
};

struct TextureStorageInfo {
	IMAGE_FILE_TYPE imageFileType;	
	TEXEL_FORMAT format;	
	unsigned width;
	unsigned height;
	unsigned depth;
	unsigned mipLevels;
	unsigned components;
	unsigned faces;
};

enum IMAGE_FILE_TYPE { IMAGE_FILE_TYPE_UNKNOWN, IMAGE_FILE_TYPE_TGA, IMAGE_FILE_TYPE_DDS };

class TextureStorage : public Referenced {

	TextureStorageInfo info;

	//TextureMipLevel mips[ 6 ][ MAX_MIPMAPS ];		
	//TEXTURE_TYPE type;
	//SharedPtr<core::IBuffer> image;
	//SharedPtr<core::ICoreSystem> coreSystem;
	//void imgRGB8toBGR8();   
	//bool loadTGA( const XResourceName &fileName );

	int getImageSize( const PIXEL_FORMAT format, int w, int h, int d, int nMipMapLevels );
	int getMipMappedSize( const int firstMipMap, int nMipMapLevels );
	
public:
	
	/*
	uint getWidth( uint mipLevel = 0 ) const { return( width ); }
	uint getHeight( uint mipLevel = 0 ) const { return( height ); }
	uint getDepth( uint mipLevel = 0 ) const { return( depth ); }
	uint getMipLevels() const { return( mipLevels ); }

	uint getOffset( uint mipLevel ) const;
	uint getOffset( FACE_TYPE face, uint mipLevel ) const;
	uint getOffset3D(FACE_TYPE face, uint mipLevel) const;
	//core::IBuffer* getMipLevelData( uint mipLevel ) const;
	//core::IBuffer* getMipLevelData( uint mipLevel, FACE_INDEX face ) const;
	
	bool isCube() const;
	bool isVolume() const;
	*/

	//PIXEL_FORMAT getFormat() const { return( format ); }
	//core::IBuffer *getImageData() const { return( image ); }

	//bool asTGA( core::IBuffer *file );
	//bool asTGA( core::IBuffer *file, int sizeX, int sizeY, int bpp );

	//bool asDDS( core::IBuffer *file );
	//bool load( const XResourceName &resourceName, TEXTURE_TYPE textureType = TEXTURE_TYPE_NONE );
	//bool saveImage( const XResourceName &resourceName );

};


