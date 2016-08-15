#pragma once

#ifndef IMAGE_FILE_HPP
#define IMAGE_FILE_HPP

#include "MemoryBuffer.hpp"
#include "File.hpp"
#include "HardwareTexture.hpp"



/*
struct TgaHeader {

	byte numIden;
	byte colorMapType;
	byte imageType;
	byte colorMapSpec[ 5 ];
	byte origX[ 2 ];
	byte origY[ 2 ];
	byte width[ 2 ];
	byte height[ 2 ];
	byte bpp;
	byte imageDes; 

	TgaHeader() { memset( (void*)this, 0, sizeof(TgaHeader) ); }

};

// DDS

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
*/

/*
struct MipLevel {
	uint width, height, depth;
	size_t offset;
	size_t size;
	MipLevel() : width( 0 ), height( 0 ), depth( 0 ), offset( 0 ), size( 0 ) {}
};
*/

enum IMAGE_FILE_TYPE { IMAGE_FILE_UNKNOWN, IMAGE_FILE_TGA, IMAGE_FILE_DDS };

struct ImageFileInfo {
	
	IMAGE_FILE_TYPE imageFileType;

	CommonTextureInfo textureInfo;

	/*
	TEXEL_FORMAT texelFormat;
	
	TEXTURE_TYPE textureType;

	unsign width;
	uint height;
	uint depth;
	uint mipLevels;
	uint components;
	uint faces;
	*/

};


class TextureFile : public Referenced {

	ImageFileInfo info;
	//IMAGE_FILE_TYPE imageFileType;

	SharedPtr<TextureSurface> arrayes[ MAX_MIPMAPS ];
  SharedPtr<TextureSurface> faces[ 6 ][ MAX_MIPMAPS ];
	SharedPtr<TextureVolume> volumes[ MAX_MIPMAPS ];

	/*
	SmartPtr<core::IBuffer> image;
	SmartPtr<core::ICoreSystem> coreSystem;

	void imgRGB8toBGR8();   
	bool loadTGA( const XResourceName &fileName );
	int getImageSize( const PIXEL_FORMAT format, int w, int h, int d, int nMipMapLevels );
	int getMipMappedSize( const int firstMipMap, int nMipMapLevels );	
	*/

public:

	TextureFile() {
		//format = PIXEL_FORMAT_NONE;
	}

	/*
	XImage( uint _width = 0, 
		uint _height = 0, 
		uint _depth = 0, 
		uint components = 0 ) {

	}
	*/

	unsigned getWidth( uint mipLevel = 0 ) const { return( 0 ); }
	unsigned getHeight( uint mipLevel = 0 ) const { return( 0 ); }
	unsigned getDepth( uint mipLevel = 0 ) const { return( 0 ); }
	unsigned getMipLevels() const { return( 0 ); }
	

	TextureSurface* getSurface(FACE_TYPE type, unsigned mipLevel) const { return NULL; }
	TextureSurface* getSurface(unsigned layer, unsigned mipLevel) const { return NULL; };
	TextureSurface* getSurface(unsigned mipLevel) const { return NULL; };
	TextureVolume* getVolume(unsigned mipLevel) const { return NULL; };

	//uint getOffset( uint mipLevel ) const;
	//uint getOffset( FACE_INDEX face, uint mipLevel ) const;
	//uint getOffset3D( FACE_INDEX face, uint mipLevel ) const;
	//core::IBuffer* getMipLevelData( uint mipLevel ) const;
	///core::IBuffer* getMipLevelData( uint mipLevel, FACE_INDEX face ) const;

	bool isCube() const { return info.textureInfo.type == TEXTURE_CUBE; }
	bool isVolume() const{ return info.textureInfo.type == TEXTURE_3D; }
	bool isArray() const{ return info.textureInfo.type == TEXTURE_2D_ARRAY; }


	//PIXEL_FORMAT getFormat() const { return( format ); }
	//core::IBuffer *getImageData() const { return( image ); }

	//bool asTGA( core::IBuffer *file );
	//bool asTGA( core::IBuffer *file, int sizeX, int sizeY, int bpp );
	//bool asDDS( core::IBuffer *file );


	//bool load( const XResourceName &resourceName, TEXTURE_TYPE textureType = TEXTURE_TYPE_NONE );
	//bool saveImage( const XResourceName &resourceName );

};

//XImage asTGA( std::vector<byte> &array );
//bool createFileTGA( std::string &fileName, std::vector<byte> &dataArray, int sizeX, int sizeY, int bpp );
//void imgRGB8toBGR8( XImage &image );


//XImage RGB8toRGBA8( XImage &srcImage );


#endif //IMAGE_H