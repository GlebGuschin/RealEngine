#pragma once

#ifndef __COLOR_HPP__
#define __COLOR_HPP__


#include "Archive.hpp"
#include "MathCommon.hpp"

class Color {

	float r, g, b, a;

public:


	inline float getRed() const { return( r ); }
	inline float getBlue() const { return( b ); }
	inline float getGreen() const { return( g ); }
	inline float getAlpha() const { return( a ); }

	inline void setRed(float r_) { r = r_; }
	inline void setBlue(float b_) { b = b_; }
	inline void setGreen(float g_) { g = g_; }
	inline void setAlpha(float a_) { a = a_; }

	void setValue( float r_, float g_, float b_, float a_ )  {
	
		r = (float)r_;
		g = (float)g_;
		b = (float)b_;
		a = (float)a_;

	}

	Color() { setValue( 0.0, 0.0, 0.0, 1.0 ); }
	Color( double r_, double g_, double b_, double a_ = 1.0 ) {
		setValue( (float)r_, (float)g_, (float)b_, (float)a_ );
	}

	Color( float r_, float g_, float b_, float a_ = 1.0 ) {
		setValue( (float)r_, (float)g_, (float)b_, (float)a_ );
	}

	Color& operator*=( const float scale ) { r *= scale; g *= scale; b *= scale; a *= scale; return( *this ); }
	Color& operator*=( const double scale ) { r *= (float)scale; g *= (float)scale; b *= (float)scale; a *= (float)scale; return( *this ); }


	Color& operator*=(const Color&color) { r *= color.r; g *= color.g; b *= color.b; a *= color.a; return(*this); }
	Color& operator+=(const Color&color) { r += color.r; g += color.g; b += color.b; a += color.a; return(*this); }

	bool operator==(const Color&other) const {
		const float esp = 0.001f;
		return fabs(a - other.a) < esp && fabs(r - other.r) < esp && fabs(g - other.g) < esp && fabs(b - other.b) < esp;			
	}

	
	inline operator uint32() const {

		//saturate();

		byte _r = byte(r * 255.0f);
		byte _g = byte(g * 255.0f);
		byte _b = byte(b * 255.0f);
		byte _a = byte(a * 255.0f);

		return( (_r << 24) | (_g << 16) | (_b << 8 ) | _a );

	}
	

	Color bgra() const{ return( Color( b, g, r, a ) ); }
	Color argb() const{ return( Color( a, r, g, b ) ); }

	Color gamma() const{ return(Color(a, r, g, b)); }


	
	friend Archive& operator << ( Archive &archive, Color &color ) { return( archive << color.r << color.g << color.b << color.a ); }
	

	const static Color BLACK;
	const static Color RED;
	const static Color GREEN;
	const static Color BLUE;
	const static Color WHITE;
	const static Color GRAY;
	const static Color YELLOW;
	const static Color CYAN;
	const static Color PINK;

	
	static Color Random();
	
	friend Color operator * ( const Color &color, float scale ) { return( Color( color.r * scale, color.g * scale, color.b * scale ) ); }
	friend Color operator + (const Color &color1, const Color &color2) { return(Color(color1.r + color2.r, color1.g + color2.g, color1.b + color2.b, color1.a  + color2.a)); }

};


//inline Color Lerp(const Color& color1, const Color& color2, float alpha) { return color1 * (1.0f - alpha) + color2 * alpha; }



class GammaColor {

	float r, g, b, a;

public:

	void setValue( float r_, float g_, float b_, float a_ = 1.0 ) {
			
		static const float scale = 1.0f / 2.2f;

		r = powf( r_, scale );
		g = powf( g_, scale );
		b = powf( b_, scale );
		a = powf( a_, scale );

	}			

	GammaColor( const Color& color ) { setValue( color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() ); }
	GammaColor( float r_, float g_, float b_, float a_ = 1.0 ) { 
		setValue( r_, g_, b_, a_ );
	}
	GammaColor( double r_, double g_, double b_, double a_ = 1.0 ) { 
		setValue( (float)r_, (float)g_, (float)b_, (float)a_ );
	}
	
	operator Color() const { 
		
		const float scale = 2.2f;
		return Color( powf( r, scale ), powf( g, scale ), powf( b, scale ), powf( a, scale ) );
	
	}

	friend Archive& operator << (Archive &archive, GammaColor &color) { return(archive << color.r << color.g << color.b << color.a); }
};


class PackedColor {

	//uint32 color;
	uint8 r, g, b, a;

	void setValue(float r_, float g_, float b_, float a_ = 1.0f) {

		r = byte(r_ * 255.0f);
		g = byte(g_ * 255.0f);
		b = byte(b_ * 255.0f);
		a = byte(a_ * 255.0f);

	}

public:

	PackedColor() {
		setValue( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	PackedColor(float r_, float g_, float b_, float a_ = 1.0f) {
		setValue(r_, g_, b_, a_ );
	}


	PackedColor(const Color& color) { 
		setValue(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() ); 
	}

	operator Color() const { 
		
		const float scale = 1.0f / 255.0f;
		return Color( r * scale, g * scale, b * scale, a * scale );
	
	}

	friend Archive& operator << (Archive &archive, PackedColor &color) { return(archive << color.r << color.g << color.b << color.a); }
};


struct TexCoordUV {
	float u,v;
	TexCoordUV() : u(0.0f),v(0.0f) {};
	TexCoordUV(float u_, float v_) : u(u_),v(v_) {};
	friend Archive& operator << (Archive &archive, TexCoordUV &uv) { return( archive << uv.u << uv.v ); }
};

struct TexCoordUVW : public TexCoordUV {
	float w;
	TexCoordUVW() :	TexCoordUV(), w(0.0f) {};
	TexCoordUVW(float u_, float v_, float w_) : TexCoordUV( u_, v_), w(w_){};
	//friend Archive& operator << (Archive &archive, TexCoordUV &uv) { return( archive << uv.u << uv.v ); }
};

class PackedTexCoordUV
{
	uint16 u, v;

public:

	PackedTexCoordUV(const TexCoordUV& tc) {		
		u = uint16(tc.u * 0xFFFF);
		v = uint16(tc.v * 0xFFFF);		
	}

	
	operator TexCoordUV() const {

		return TexCoordUV( float(u) / 0xFFFF, float(u) / 0xFFFF );
	}

};

struct BlendWeights {
	float weight[4];
};

struct BlendIndexes {
	byte index[4];
};


class R5G6B5Color
{
	uint16 b : 5;
	uint16 g : 6;
	uint16 r : 5;

public:

	R5G6B5Color(const Color& value) {

		//Color value = value
		r = (uint16)(value.getRed() * 32.0f);
		g = (uint16)(value.getGreen() * 64.0f);
		b = (uint16)(value.getBlue() * 32.0f);
	}

	operator Color() const {

		return Color((float)r / 32.0f, (float)g / 64.0f, (float)r / 32.0f );
	}

};


class R10G10B10A2Color
{
	uint16 r : 10;
	uint16 g : 10;
	uint16 b : 10;
	uint16 a : 2;

public:

	R10G10B10A2Color(const Color& value) {

		//Color value = value
		r = (uint16)(value.getRed() * 256.0f * 4.0f);
		g = (uint16)(value.getGreen() * 256.0f * 4.0f);
		b = (uint16)(value.getBlue() * 256.0f * 4.0f);
		a = (uint16)(value.getBlue() * 4.0f);
	}

	operator Color() const {

		return Color((float)r / 32.0f, (float)g / 64.0f, (float)r / 32.0f );
	}

};


#endif
