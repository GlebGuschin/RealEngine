#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_



#include "Vector.hpp"



class Matrix3x3 {
	
	Vector3 value[ 3 ];

public:

	Matrix3x3() { 
		value[ 0 ] = Vector3( 1.0, 0.0, 0.0 ); 	
		value[ 1 ] = Vector3( 0.0, 1.0, 0.0 ); 	
		value[ 2 ] = Vector3( 0.0, 0.0, 1.0 ); 	
	}

	inline Vector3& x() { return( value[ 0 ] ); }
	inline Vector3& y() { return( value[ 1 ] ); }
	inline Vector3& z() { return( value[ 2 ] ); }

	inline const Vector3& x() const { return( value[ 0 ] ); }
	inline const Vector3& y() const { return( value[ 1 ] ); }
	inline const Vector3& z() const { return( value[ 2 ] ); }

	friend Vector3 operator *( const Matrix3x3& lsh, const Vector3& rsh );

};

inline Vector3 operator *( const Matrix3x3& lsh, const Vector3& rsh ) {
	Real x = dot( lsh.x(), rsh );
	Real y = dot( lsh.y(), rsh );
	Real z = dot( lsh.z(), rsh );
	return( Vector3( x, y, z ) ); 
}








class Matrix4x4 {
	
	Vector4 value[ 4 ];

public:

	Matrix4x4() { 
		value[ 0 ] = Vector4( 1.0, 0.0, 0.0, 0.0 ); 	
		value[ 1 ] = Vector4( 0.0, 1.0, 0.0, 0.0 ); 	
		value[ 2 ] = Vector4( 0.0, 0.0, 1.0, 0.0 ); 	
		value[ 3 ] = Vector4( 0.0, 0.0, 0.0, 1.0 ); 
	}

	Matrix4x4( const Vector4& v0,  const Vector4& v1,  const Vector4& v2,  const Vector4& v3)  { 
		value[ 0 ] = v0;
		value[ 1 ] = v1; 	
		value[ 2 ] = v2; 	
		value[ 3 ] = v3; 	
	}

	inline Vector4& x() { return( value[ 0 ] ); }
	inline Vector4& y() { return( value[ 1 ] ); }
	inline Vector4& z() { return( value[ 2 ] ); }
	inline Vector4& w() { return( value[ 3 ] ); }

	inline const Vector4& x() const { return( value[ 0 ] ); }
	inline const Vector4& y() const { return( value[ 1 ] ); }
	inline const Vector4& z() const { return( value[ 2 ] ); }
	inline const Vector4& w() const { return( value[ 3 ] ); }

	Vector4& operator[]( size_t index ) { assert( index < 4 );  return( value[ index ] ); }
	const  Vector4& operator[]( size_t index ) const { assert( index < 4 );  return( value[ index ] ); }

	Vector3 getTranslate() { return Vector3(); }
	void  setTranslate(const Vector3& ) {  }

	Real getValue(uint32 x, uint32 y) { assert(x < 4 && y < 4); return value[y][x]; }
	inline Vector4 getColumn( size_t index ) const { assert( index < 4 ); return( Vector4( value[ 0 ][ index ], value[ 1 ][ index ], value[ 2 ][ index ], value[ 3 ][ index ]  ) ); }

	friend Matrix4x4 operator *( const Matrix4x4& lsh, const Matrix4x4& rsh );
	friend Vector4 operator *( const Matrix4x4& lsh, const Vector4& rsh );

	static const Matrix4x4 Zero;
	static const Matrix4x4 Identity;

	static Matrix4x4 RotationZ(float angle) {
	
		Matrix4x4 matrix;
		return  matrix;
	
	}

	static Matrix4x4 Rotate(const Vector3& vec, const float angle);

};

typedef Matrix4x4 Matrix;

inline Matrix4x4 operator *( const Matrix4x4& lsh, const Matrix4x4& rsh ) {

	Matrix4x4 matrix4x4;

	for( size_t i = 0; i < 4; i++ ) {
			Vector4	row = lsh[ i ];	

			Vector4	newRow;
			for( size_t j = 0; j < 4; j++ ) {
					Vector4 column = rsh.getColumn( j ); 
					//Vector4 column; 
					newRow[ j ] = dot( row, column );
			}
			matrix4x4[ i ] = newRow;
	}

	return( matrix4x4 );
}
	
inline Vector4 operator *( const Matrix4x4& lsh, const Vector4& rsh ) {
	Real x = dot( lsh.x(), rsh );
	Real y = dot( lsh.y(), rsh );
	Real z = dot( lsh.z(), rsh );
	Real w = dot( lsh.w(), rsh );
	return( Vector4( x, y, z, w ) ); 
}


Matrix4x4 BuildRotateMatrix(const Vector3& axis, float angle);



class Matrix3x4 {
	
	Vector4 value[ 3 ];

public:

	Matrix3x4( const Vector4& v0,  const Vector4& v1,  const Vector4& v2 ) {
	

	}

	operator Matrix4x4() const { return Matrix4x4(value[0], value[1], value[2], Vector4(0.0f, 0.0f, 0.0f, 1.0f)); }

};

/*
class Transform {

	Matrix4x4 matrix;
	int i;

public:

	Transform() {}
	Transform( const Matrix4x4& matrix_ ) : matrix( matrix_ ) {}

	Vector3 getAxis( enum AXIS ) { return( Vector3() ); }
	Vector3 getTranslate() { return( Vector3() ); }
	Matrix3x3 getBasis() { return( Matrix3x3() ); }

	const Matrix4x4&  getMatrix() const { return( matrix ); }

	void applyTransform( const Transform& transform );
	void applyLocalTransform( const Transform& transform );

	void applyTranslate( const Vector3 & translate );
	void applyLocalTranslate( const Vector3 & translate );

	void applyScale( float a, float b, float c );
	void applyLocalScale( float a, float b, float c );

	const static Transform Identity;

};


inline Transform operator * ( const Transform& lhs, const Transform& rhs ) { return( Transform()  ); } 

class TransformStack { 

	std::vector<Transform> stack;

public:

	TransformStack() {}
	~TransformStack() {}

};

*/



struct Plane {

	Vector3 normal;
	float D;
	Plane() {}

	const Vector3& getNormal() const { return( normal ); }
	float getDistanse() const { return( D ); }
	
	Vector3& getNormal()  { return( normal ); }
	float& getDistanse() { return( D ); }

	float calcDistance(const Vector3& point) const { return DotProduct(normal, point) + D; }
	
};


class Sphere {

	Vector3 origin;
	float radius;
	float radius2;

public:

	Sphere() : origin( Vector3() ), radius( 1.0f ) {}
	Sphere( const Vector3& origin_, float radius_ ) : origin( origin_ ), radius( radius_ ) { radius2 = radius * radius; }
	
	const Vector3& getOrigin() const { return( origin ); }
	float getRadius() const { return( radius ); }

	bool calcIntersection( const Vector3& position ) const {
	
		Vector3 diff = origin - position;

		return( DotProduct( diff, diff ) <= radius2 );
	
	}

	friend Archive& operator << ( Archive &archive, Sphere &sphere );

};


class Ray {
	Vector3 origin;
	Vector3 direction;
public:

	Ray( const Vector3 &origin_, const Vector3 &direction_ ) : origin( origin_ ), direction( Normalize( direction_ ) ) {}

	Vector3 calcPosition( float t ) { return( origin + direction * t ); }

	friend Archive& operator << ( Archive &archive, Ray &ray );

};


class BoundBox {
protected:
	Vector3 origin, extent;
public:
	BoundBox() {}
	BoundBox(const Vector3& origin_, const Vector3& extent_) {}
	friend Archive& operator << (Archive &archive, BoundBox &box);
};

class BoundSphereBox : public BoundBox {
	float radius;
public:
	BoundSphereBox() {}
	BoundSphereBox(const Vector3& origin_, const Vector3& extent_, const float radius_ ) {}
	friend Archive& operator << (Archive &archive, BoundSphereBox &box);
};


class TransformedBoundSphereBox {
	
	Matrix4x4 transform;
	BoundSphereBox boundSphereBox;


	
public:

	TransformedBoundSphereBox(const BoundSphereBox& boundSphereBox_, const Matrix4x4& transform_) {}
	
	///friend Archive& operator << ( Archive &archive, BoundBox &box );

};



enum FRUSTUM_CULL_TYPE { FRUSTUM_CULL_IN, FRUSTUM_CULL_OUT, FRUSTUM_CULL_INTERSECT };

class Frustum {

	Array<Plane,6> planes;

	void build(float fovy, float aspect, float zNear, float zFar);

public:

	enum FRUSTUM_PLANES { PLANE_NEAR = 0, PLANE_FAR, PLANE_LEFT, PLANE_RIGHT, PLANE_DOWN, PLANE_TOP };

	Frustum() {}
	Frustum(float fovy, float aspect, float zNear, float zFar) { build(fovy, aspect, zNear, zFar); }

	FRUSTUM_CULL_TYPE checkIntersection( const Sphere &sphere );
	const Plane& getPlane( FRUSTUM_PLANES plane ) const { return( planes[ plane ] ); }

};


 
Archive& operator << ( Archive &archive, Vector3 &vector );
Archive& operator << ( Archive &archive, Matrix3x3 &matrix );
Archive& operator << ( Archive &archive, Vector4 &vector );
Archive& operator << ( Archive &archive, Matrix4x4 &matrix );

//Archive& operator << ( Archive &archive, Sphere &sphere );
Archive& operator << ( Archive &archive, Plane &plane );
//Archive& operator << ( Archive &archive, Ray &ray );




class Quaternion {
	
	float  array[4];					

	void setValue(const Vector3 &axis, float theta);
	void setValue(const Matrix4x4& matrix);

public:

	Quaternion() {}
	Quaternion(const Vector3& axis, float angle) { setValue(axis, angle); }
	Quaternion(const Matrix4x4& matrix) { setValue(matrix); }

	Matrix4x4 getMatrix() const;

	inline float x() const { return array[0]; }
	inline float y() const { return array[1]; }
	inline float z() const { return array[2]; }
	inline float w() const { return array[3]; }

	friend Quaternion operator *(const Quaternion& lsh, const Quaternion& rsh);

};

inline Quaternion operator *(const Quaternion& ql, const Quaternion& qr) {

	Quaternion q;

	q.array[3] = ql.w() * qr.w() - ql.x() * qr.x() - ql.y() * qr.y() - ql.z() * qr.z();
	q.array[0] = ql.w() * qr.x() + ql.x() * qr.w() + ql.y() * qr.z() - ql.z() * qr.y();
	q.array[1] = ql.w() * qr.y() + ql.y() * qr.w() + ql.z() * qr.x() - ql.x() * qr.z();
	q.array[2] = ql.w() * qr.z() + ql.z() * qr.w() + ql.x() * qr.y() - ql.y() * qr.x();

	return q;
}

bool Compare(const Matrix4x4& a, const Matrix4x4& b, const float error=0.001f);


#endif
