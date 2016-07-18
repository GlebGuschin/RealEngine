#pragma once
#ifndef _MATH_COOMMON_HPP_
#define _MATH_COOMMON_HPP_



#include <assert.h>

#include <math.h>

#include "Common.hpp"

#define PI                 3.14159265358f
#define VECTOR_EPSILON     0.001


class Vector3;
class Matrix3x3;
class Vector4;
class Matrix4x4;
class Transform;
class Quaternion;

typedef float Real; 



inline float DegToRad( float angle ) { return( float( PI / 180.0 * angle ) ); }
inline float RadToDeg( float rad ) { return( float( 180.0 / PI * rad ) ); }

template <class T>
inline bool IsEqual( T a, T b, T eps ) { return( fabs( a - b ) <= eps ); }

template <class T1, class T2>
inline T1 Lerp( const T1& a, const T1& b, T2 alpha ) { return( a * ( 1.0f - alpha ) + b * alpha ); }

template <class T>
inline T Clamp(const T& value, const T& minValue, const T& maxValue ) { 
	if (value < minValue) retun  minValue;
	if (value > maxValue) retun  maxValue;
	return( value ); 
}

///inline float (float rad) { return(float(180.0 / PI * rad)); }
inline float FloatRandom() { int i = rand() & 127;  return( (float) i / (float)127 ); }

template <class T>
inline T HermiteLerp(const T& a, const T& b, T alpha) { return( a * alpha * alpha * 3 + b * 2 * alpha * alpha * alpha ); }

//template <class T>
//inline T Convert2Positive(T value) {}


inline float NDC(float value) { return value * 0.5f + 0.5f; }
inline float FNDC(float value) { return (value - 0.5f) * 2.0f; }

inline uint16 PackU16(float value) { return ( (uint16)((value / (float)0x9FFF) * 0.5f + 0.5f) * 0x9FFF); }
inline float UnpackU16(uint16 packedValue) { return (((float)packedValue / 0x9FFF - 0.5f) * 2.0f) * 0x9FFF; }

#endif