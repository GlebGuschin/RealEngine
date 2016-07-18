

#include "stdafx.h"


#include "Vector.hpp"
#include "Matrix.hpp"
#include "Transform.hpp"

#include "Archive.hpp"

/*
Archive& operator << ( Archive &archive, Vector3 &vector ) {
	return( archive << vector.x() << vector.y() << vector.z() );
}
*/

Archive& operator << ( Archive &archive, Matrix3x3& matrix ) {
	return( archive << matrix.x() << matrix.y() << matrix.z() );
}

Archive& operator << ( Archive &archive, Vector4 &vector ) {
	return( archive << vector.x() << vector.y() << vector.z() << vector.w() );
}

Archive& operator << ( Archive &archive, Matrix4x4 &matrix ) {
	return( archive << matrix.x() << matrix.y() << matrix.z() << matrix.w() );
}


Archive& operator << ( Archive &archive, Ray &ray ) {
	return( archive << ray.origin << ray.direction );
}

Archive& operator << ( Archive &archive, Sphere &sphere ) {
	return( archive << sphere.origin << sphere.radius << sphere.radius2 );
}

Archive& operator << ( Archive &archive, BoundBox &box ) {
	//archive << box.origin << box.bounds;
	for( int i = 0; i < 8; i++ ) {
				//archive << box.corners[ i ];
	}
	return( archive );
}

/*
Vector4 min( const Vector4& lsh, const Vector4& rsh ) { 

	Vector4 vector( std::min( lsh.x(), rsh.x() ), std::min( lsh.y(), rsh.y() ), std::min( lsh.z(), rsh.z() ), std::min( lsh.w(), rsh.w() ) ); 
	return( vector );

}

Vector4 max( const Vector4& lsh, const Vector4& rsh ) { 

	Vector4 vector( std::max( lsh.x(), rsh.x() ), std::max( lsh.y(), rsh.y() ), std::max( lsh.z(), rsh.z() ), std::max( lsh.w(), rsh.w() ) ); 
	return( vector );

}
*/



const Vector3 Vector3::XAXIS = Vector3( 1.0, 0.0, 0.0 );
const Vector3 Vector3::YAXIS = Vector3(0.0, 1.0, 0.0);
const Vector3 Vector3::ZAXIS = Vector3(0.0, 0.0, 1.0);






Vector3 CrossProduct( const Vector3 &lhs, const Vector3 &rhs ) {
   
 return( Vector3( lhs.y() * rhs.z() - lhs.z() * rhs.y(), lhs.z() * rhs.x() - lhs.x() * rhs.z(), lhs.x() * rhs.y() - lhs.y() * rhs.x() ) );

}                      

//Real DotProduct( const Vector3& lsh, const Vector3& rsh ) { return( lsh.x() * rsh.x() + lsh.y() * rsh.y() + lsh.z() * rsh.z()); }



Matrix4x4 BuildRotateMatrix(const Vector3& axis_, float angle) {

	Matrix4x4 out;
	Vector3 axis;
	float cosine, sine;
	float COS;

	float l, m, n;

	axis = Normalize(axis_);
	//axis = vec;
	cosine = cos(Deg2Rad(angle));
	sine = sin(Deg2Rad(angle));

	l = axis.x();
	m = axis.y();
	n = axis.z();

	COS = 1 - cosine;

	out[0][0] = l * l + (1 - l * l) * cosine;
	out[0][1] = l * m * COS + n * sine;
	out[0][2] = l * n * COS - m * sine;
	out[0][3] = 0.0f;

	out[1][0] = l * m * COS - n * sine;
	out[1][1] = m * m + (1 - m * m) * cosine;
	out[1][2] = m * n * COS + l * sine;
	out[1][3] = 0.0f;

	out[2][0] = l * n * COS + m * sine;
	out[2][1] = m * n * COS - l * sine;
	out[2][2] = n * n + (1 - n * n) * cosine;
	out[2][3] = 0.0f;

	return(out);

}





void Transform::applyTransform( const Transform& transform ) {

	//matrix = transform.matrix * matrix;

}

void Transform::applyLocalTransform( const Transform& transform ) {

	//matrix = matrix * transform.matrix;

}

void Transform::applyTranslate( const Vector3 & translate ) {

}

void Transform::applyLocalTranslate( const Vector3 & translate ) {


}




void Frustum::build(float fovy, float aspect, float zNear, float zFar) {

	/*
	vec4f  left(1, 0, 0, 1),
	right(-1, 0, 0, 1),
	up(0, -1, 0, 1),
	down(0, 1, 0, 1),
	forward(0, 0, 1, zNear);

	float halfY = fovy * 0.5;
	float halfX = halfY * aspect;

	left = rotate(vec3f(0, 1, 0), halfX) * left;
	right = rotate(vec3f(0, 1, 0), -halfX) * right;
	up = rotate(vec3f(1, 0, 0), halfY) * up;
	down = rotate(vec3f(1, 0, 0), -halfY) * down;


	frustrumInfo.planes.clear();
	frustrumInfo.planes.push_back(left);
	frustrumInfo.planes.push_back(right);
	frustrumInfo.planes.push_back(up);
	frustrumInfo.planes.push_back(down);
	frustrumInfo.planes.push_back(forward);
	*/

}


FRUSTUM_CULL_TYPE Frustum::checkIntersection(const Sphere &sphere) {

	uint32 positive = 0, negative = 0;

	for (uint32 i = 0; i < 6; i++) { 

		const float distance = planes[i].calcDistance(sphere.getOrigin() );
		if (distance > 0.0 ) {
			return FRUSTUM_CULL_OUT;
		}		
		negative++;
		
	}
		
	if (negative == 6) return FRUSTUM_CULL_IN;

	return FRUSTUM_CULL_INTERSECT;

}







//