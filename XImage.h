#pragma once

#ifndef IMAGE_HPP
#define IMAGE_HPP


#include "X.h"


namespace x {

namespace render {


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
/*
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
enum PIXEL_FORMAT {

	PIXEL_FORMAT_NONE,
	PIXEL_FORMAT_RGBA8,
	PIXEL_FORMAT_RGB8,
	PIXEL_FORMAT_DXT1,
	PIXEL_FORMAT_DXT3,
	PIXEL_FORMAT_DXT5
};

*/

struct MipLevel {
	uint width, height, depth;
	size_t offset;
	size_t size;
	MipLevel() : width( 0 ), height( 0 ), depth( 0 ), offset( 0 ), size( 0 ) {}
};


enum IMAGE_FILE_TYPE { IMAGE_FILE_TYPE_UNKNOWN, IMAGE_FILE_TYPE_TGA, IMAGE_FILE_TYPE_DDS };

class XImage : public XUnknown {


	MipLevel mips[ 6 ][ MAX_MIPMAPS ];
	
	IMAGE_FILE_TYPE imageFileType;
	
	PIXEL_FORMAT format;
	
	TEXTURE_TYPE type;

	uint width;
	uint height;
	uint depth;
	uint mipLevels;
	uint components;
	uint faces;


	SmartPtr<core::IBuffer> image;
	SmartPtr<core::ICoreSystem> coreSystem;

	void imgRGB8toBGR8();
   

	bool loadTGA( const XResourceName &fileName );


	int getImageSize( const PIXEL_FORMAT format, int w, int h, int d, int nMipMapLevels );
	int getMipMappedSize( const int firstMipMap, int nMipMapLevels );
	
public:

	XImage( core::ICoreSystem *coreSystem_ ) : coreSystem( coreSystem_ ) {


		format = PIXEL_FORMAT_NONE;

	}

	/*
	XImage( uint _width = 0, 
		uint _height = 0, 
		uint _depth = 0, 
		uint components = 0 ) {

	}
	*/

	uint getWidth( uint mipLevel = 0 ) const { return( width ); }
	uint getHeight( uint mipLevel = 0 ) const { return( height ); }
	uint getDepth( uint mipLevel = 0 ) const { return( depth ); }
	uint getMipLevels() const { return( mipLevels ); }


	uint getOffset( uint mipLevel ) const;
	uint getOffset( FACE_INDEX face, uint mipLevel ) const;
	uint getOffset3D( FACE_INDEX face, uint mipLevel ) const;
	core::IBuffer* getMipLevelData( uint mipLevel ) const;
	core::IBuffer* getMipLevelData( uint mipLevel, FACE_INDEX face ) const;


	bool isCube() const;
	bool isVolume() const;


	PIXEL_FORMAT getFormat() const { return( format ); }
	core::IBuffer *getImageData() const { return( image ); }


	bool asTGA( core::IBuffer *file );
	bool asTGA( core::IBuffer *file, int sizeX, int sizeY, int bpp );

	bool asDDS( core::IBuffer *file );


	bool load( const XResourceName &resourceName, TEXTURE_TYPE textureType = TEXTURE_TYPE_NONE );
	bool saveImage( const XResourceName &resourceName );

};

//XImage asTGA( std::vector<byte> &array );
//bool createFileTGA( std::string &fileName, std::vector<byte> &dataArray, int sizeX, int sizeY, int bpp );
//void imgRGB8toBGR8( XImage &image );




XImage RGB8toRGBA8( XImage &srcImage );

};

};

#endif //IMAGE_H