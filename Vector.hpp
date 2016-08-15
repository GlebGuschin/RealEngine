#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_



//#endif

#include "MathCommon.hpp"
#include "Archive.hpp"

#define PI                 3.14159265358f
#define EPSILON				0.001f


inline float Deg2Rad(float angle) { return float(PI / 180.0 * angle); }
inline float Rad2Deg(float rad) { return float(180.0 / PI * rad); }

//inline float FloatRandom() { return (float)rand() / (float)INT_MAX; }

template<typename T>
T Min(const T& a, const T& b) { return a < b ? a : b; }

template<typename T>
T Max(const T& a, const T& b) { return a > b ? a : b; }

inline float Random(float min, float max) { return (max + min) * 0.0f;  }



class Vector3;
class Vector4;

enum AXIS { AXIS_X = 0, AXIS_Y = 1, AXIS_Z = 2 };

class Vector3 {

	//Real x, y, z;
	Real arr[ 3 ];

	void setValue( const Real& x_, const Real& y_, const Real& z_ ) {
			arr[ 0 ] = x_;
			arr[ 1 ] = y_;
			arr[ 2 ] = z_;
	}


public:

	Vector3() { arr[ 0 ] = arr[ 1 ] = arr[ 2 ] = 0.0; }
	Vector3( const Real& x_, const Real& y_, const Real& z_ ) { setValue( x_, y_, z_ ); }
	Vector3( const Real& x_ ) { setValue( x_, x_, x_ ); }
	Vector3(const Vector4& vector);



	inline Real& x() { return( arr[ 0 ] ); }
	inline Real& y() { return( arr[ 1 ] ); }
	inline Real& z() { return( arr[ 2 ] ); }

	inline const Real& x() const { return( arr[ 0 ] ); }
	inline const Real& y() const { return( arr[ 1 ] ); }
	inline const Real& z() const { return( arr[ 2 ] ); }

	friend Archive& operator << (Archive &archive, Vector3 &v) { return(archive << v.x() << v.y() << v.z() ); }


	Vector3 operator-() { return( Vector3( -x(), -y(), -z() ) ); }

	Vector3& normalizeUnsafe() {
		const Real inVdotValue = 1.0f / dot(*this, *this);
		arr[0] *= inVdotValue; arr[1] *= inVdotValue; arr[2] *= inVdotValue;
		return (*this);
	}


	Vector3& mormalize() { 
		Real dotValue = dot(*this, *this); 
		if (dotValue > 0.0f) {

		} else {
			*this = Vector3();
		}
		return (*this);
	}


	friend Vector3 operator +( const Vector3& lsh, const Vector3& rsh );
	friend Vector3 operator -( const Vector3& lsh, const Vector3& rsh );
	friend Vector3 operator *( const Vector3& lsh, const Real scalar );
	friend Vector3 operator /( const Vector3& lsh, const Real scalar );
	friend Vector3 operator *(const Vector3& lsh, const Vector3& rsh);
	
	friend Real dot( const Vector3& lsh, const Vector3& rsh );

	static const Vector3 XAXIS, YAXIS, ZAXIS;

	//static Vector3 Random() { return Vector3( Random(), Random(), Random() ); }
	static Vector3 Random() { return Vector3(); }


 bool operator < (const Vector3& v) const 
  {
    if (x() != v.x() ) {
      return x() < v.x();
    }
    if (y() != v.y()) {
      return y() < v.y();
    }
    if (z() != v.z()) {
      return z() < v.z();
    }
    return false;
  }


};

//Vector3 operator +( const Vector3& lsh, const Vector3& rsh ) { return( Vector3( ) ); }
inline Vector3 operator +( const Vector3& lsh, const Vector3& rsh ) { return( Vector3( lsh.x() + rsh.x(), lsh.y() + rsh.y(), lsh.z() + rsh.z() ) ); }
inline Vector3 operator -( const Vector3& lsh, const Vector3& rsh ) { return( Vector3( lsh.x() - rsh.x(), lsh.y() - rsh.y(), lsh.z() - rsh.z() ) ); }
inline Vector3 operator *( const Vector3& lsh, const Real scalar ) { return( Vector3( lsh.x() * scalar, lsh.y() * scalar, lsh.z() * scalar  ) ); }
inline Vector3 operator /( const Vector3& lsh, const Real scalar ) { Real dem = (Real)1.0 / scalar; return(  lsh * dem ); }


inline Vector3 operator /( const Vector3& lsh, const Real scalar );

inline Vector3 operator *( const Vector3& lsh, const Vector3& rsh ) { 
	return( Vector3( lsh.x() * rsh.x(), lsh.y() * rsh.y(), lsh.z() * rsh.z() ) );
}
	
inline Real DotProduct( const Vector3& lsh, const Vector3& rsh ) { return( lsh.x() * rsh.x() + lsh.y() * rsh.y() + lsh.z() * rsh.z()); }

inline Vector3 Normalize( const Vector3& vector ) {
	Real inv = DotProduct( vector, vector );
	assert( inv != (Real)0.0 );
	return( vector / sqrt( inv ) );
} 


inline Vector3 NormalizeUnsafe(const Vector3& vector) {
	const Real inv = 1.0f / DotProduct(vector, vector);	
	return(vector * inv);
}

inline Vector3 Abs( const Vector3& vector ) { return( Vector3( fabs( vector.x() ), fabs( vector.y() ), fabs( vector.z() ) ) ); }

inline bool IsEqual( const Vector3& lsh, const Vector3& rsh, Real epsilon = 0.0001f ) { 
	Vector3 vector = Abs( lsh - rsh );
	return( vector.x() < epsilon && vector.y() < epsilon && vector.z() < epsilon ); 
}

/*
inline bool CheckBound(const Vector3& point, const Vector3& bound) {
	//Vector3 vector = Abs(lsh - rsh);
	return( vector.x() < epsilon && vector.y() < epsilon && vector.z() < epsilon);
}
*/


inline Vector3 Min( const Vector3& v1, const Vector3& v2 ) { 
	return Vector3( Min( v1.x(), v2.x() ), Min( v1.y(), v2.y() ), Min( v1.z(), v2.z() ) ); 
}

inline Vector3 Max( const Vector3& v1, const Vector3& v2 ) { 
	return Vector3( Max( v1.x(), v2.x() ), Max( v1.y(), v2.y() ), Max( v1.z(), v2.z() ) ); 
}

class Vector4 {

	//Real x, y, z;
	Real value[ 4 ];

	void setValue( const Real& x_, const Real& y_, const Real& z_,  const Real& w_ = 1.0 ) {
		value[ 0 ] = x_;
		value[ 1 ] = y_;
		value[ 2 ] = z_;
		value[ 3 ] = w_;	
	}

public:


	inline Real& x() { return( value[ 0 ] ); }
	inline Real& y() { return( value[ 1 ] ); }
	inline Real& z() { return( value[ 2 ] ); }
	inline Real& w() { return( value[ 3 ] ); }

	inline const Real& x() const { return( value[ 0 ] ); }
	inline const Real& y() const { return( value[ 1 ] ); }
	inline const Real& z() const { return( value[ 2 ] ); }
	inline const Real& w() const { return( value[ 3 ] ); }


	Vector4() { value[ 0 ] = value[ 1 ] = value[ 2 ] = 0.0; value[ 3 ] = 1.0;  }
	Vector4( const Real& x_, const Real& y_, const Real& z_,  const Real& w_ ) { setValue( x_, y_, z_, w_ ); }

	Vector4( const Real& x_, const Real& y_, const Real& z_ ) {  setValue( x_, y_, z_ );  }

	Vector4( const Vector4 &vector ) {  setValue( vector.x(), vector.y(), vector.z(), vector.w() );  }
	Vector4( const Vector3 &vector ) {  setValue( vector.x(), vector.y(), vector.z() );  }


	Vector4& operator=( const Vector4& vector ) { setValue( vector.x(), vector.y(), vector.z(), vector.w() ); return( *this ); }

	Real& operator[]( size_t index ) { assert( index < 4 );  return( value[ index ] ); }
	const Real& operator[]( size_t index ) const { assert( index < 4 );  return( value[ index ] ); }


	friend Vector4 operator +( const Vector4& lsh, const Vector4& rsh );
	friend Vector4 operator -( const Vector4& lsh, const Vector4& rsh );
	friend Real dot( const Vector4& lsh, const Vector4& rsh );

};


inline Vector4 operator +( const Vector4& lsh, const Vector4& rsh ) { return( Vector4( lsh.x() + rsh.x(), lsh.y() + rsh.y(), lsh.z() + rsh.z(), lsh.w() + rsh.w() ) ); }
inline Vector4 operator -( const Vector4& lsh, const Vector4& rsh ) { return( Vector4( lsh.x() - rsh.x(), lsh.y() - rsh.y(), lsh.z() - rsh.z(), lsh.w() - rsh.w()  ) ); }
inline Real dot( const Vector4& lsh, const Vector4& rsh ) { return( lsh.x() * rsh.x() + lsh.y() * rsh.y() + lsh.z() * rsh.z() + lsh.w() * rsh.w() ); }

//Vector4 min( const Vector4& lsh, const Vector4& rsh );
//Vector4 max( const Vector4& lsh, const Vector4& rsh );


Real DotProduct( const Vector3 &lhs, const Vector3 &rhs );
Vector3 CrossProduct( const Vector3 &lhs, const Vector3 &rhs );


typedef Vector3 Vector;

class PackedNormal
{
	uint16 x, y, z;

public:

	PackedNormal(const Vector3& normal) {
		Vector3 n = Normalize(normal) * 0.5 + Vector3(0.5, 0.5, 0.5);
		x = uint16(n.x() * 0xFFFF);
		y = uint16(n.y() * 0xFFFF);
		z = uint16(n.z() * 0xFFFF);
	}

	operator Vector3() const  {

		return Vector3((float(x) / 0xFFFF - 0.5f) * 2.0f, (float(y) / 0xFFFF - 0.5f) * 2.0f, (float(z) / 0xFFFF - 0.5f) * 2.0f);
	}

};

class PackedPosition
{
	uint16 x, y, z;

public:

	PackedPosition(const Vector3& position) {
		Vector3 p = position * 0.5f + Vector3(0.5, 0.5, 0.5);
		x = uint16(position.x() * 0xFFFF);
		y = uint16(position.y() * 0xFFFF);
		z = uint16(position.z() * 0xFFFF);
	}

	operator Vector3() const  {

		return Vector3( float(x) / 0xFFFF, float(y) / 0xFFFF, float(z) / 0xFFFF);
	}

};

//typedef PackedNormal PackedPosition;

inline Vector3::Vector3(const Vector4& vector) {
	arr[0] = vector.x() / vector.w();
	arr[1] = vector.y() / vector.w();
	arr[2] = vector.z() / vector.w();
}



class Scale3 {

	Vector3 scale;

public:

	Scale3(const Vector3& scale_) {

		//scalefabs(scale_.x()) )
	}

};






#endif

