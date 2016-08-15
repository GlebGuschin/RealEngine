#pragma once

#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__



#include "Vector.hpp"
#include "Matrix.hpp"


//enum 

class Transform {

	//Matrix4x4 matrix;
	//int i;
	Quaternion rotation;
	Vector3 position; 
	Vector3 scale;

public:

	Transform() {}
	Transform(const Matrix4x4& matrix_) {}
	Transform(const Vector3& position_, const Quaternion& rotation_, const Vector3& scale_ = Vector3( 1.0f, 1.0f, 1.0f))
		: position(position_), rotation(rotation_), scale(scale_) {}

	Vector3 getAxis(enum AXIS) { return(Vector3()); }
	Vector3 getTranslate() { return(Vector3()); }
	Vector3 getScale() const { return(Vector3()); }
	Matrix3x3 getBasis() { return(Matrix3x3()); }

	const Matrix4x4  getMatrix() const { 
		Matrix4x4  matrix;
		return( matrix ); 
	}

	void applyTransform(const Transform& transform);
	void applyLocalTransform(const Transform& transform);

	void applyTranslate(const Vector3 & translate);
	void applyLocalTranslate(const Vector3 & translate);

	void applyScale(float a, float b, float c);
	void applyLocalScale(float a, float b, float c);

	const static Transform Identity;


	bool operator ==(const Transform& other) const { return true; }
};


inline Transform operator * (const Transform& lhs, const Transform& rhs) { return(Transform()); }

class TransformStack {

	std::vector<Transform> stack;

public:

	TransformStack() {}
	~TransformStack() {}

};




class BoxSphereBounds {

	float radius;
	Vector3 extend;

public:

	BoxSphereBounds() {}
	BoxSphereBounds(float radius_) {}
	BoxSphereBounds(float radius_, const Vector3 & extend_)  {}

};


#endif
