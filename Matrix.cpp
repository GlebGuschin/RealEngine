#include "stdafx.h"
#include  "Matrix.hpp"

bool Compare(const Matrix4x4& a, const Matrix4x4& b, const float error) {

	//float error = 0.0f;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			const float delta = fabs( a[i][j] - b[i][j] );
			if (delta > error) {
				return false;
				//error = delta;
			}			
		}
	}

	return true;

}

Matrix4x4 Matrix4x4::Rotate(const Vector3& vec, const float angle) {

	Matrix4x4 out;
	Vector3 axis;
	float cosine, sine;
	float COS;

	float l, m, n;

	axis = Normalize(vec);
	//axis = vec;
	cosine = cosf(DegToRad(angle));
	sine = sinf(DegToRad(angle));

	l = axis.x();
	m = axis.y();
	n = axis.z();

	COS = 1 - cosine;

	out.value[0][0] = l * l + (1 - l * l) * cosine;
	out.value[0][1] = l * m * COS + n * sine;
	out.value[0][2] = l * n * COS - m * sine;
	out.value[0][3] = 0.0f;

	out.value[1][0] = l * m * COS - n * sine;
	out.value[1][1] = m * m + (1 - m * m) * cosine;
	out.value[1][2] = m * n * COS + l * sine;
	out.value[1][3] = 0.0f;

	out.value[2][0] = l * n * COS + m * sine;
	out.value[2][1] = m * n * COS - l * sine;
	out.value[2][2] = n * n + (1 - n * n) * cosine;
	out.value[2][3] = 0.0f;

	return(out);

}


Matrix4x4 Quaternion::getMatrix() const {

	Matrix4x4 m;

	float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

	float norm = array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3];

	s = (norm == 0.0f) ? 0.0f : 2.0f / norm;

	xs = array[0] * s;
	ys = array[1] * s;
	zs = array[2] * s;

	wx = array[3] * xs;
	wy = array[3] * ys;
	wz = array[3] * zs;

	xx = array[0] * xs;
	xy = array[0] * ys;
	xz = array[0] * zs;

	yy = array[1] * ys;
	yz = array[1] * zs;
	zz = array[2] * zs;

	m[0][0] = 1.0f - (yy + zz);
	m[1][0] = (xy + wz);
	m[2][0] = (xz - wy);

	m[0][1] = (xy - wz);
	m[1][1] = 1.0f - (xx + zz);
	m[2][1] = (yz + wx);

	m[0][2] = (xz + wy);
	m[1][2] = (yz - wx);
	m[2][2] = 1.0f - (xx + yy);

	m[3][0] = m[3][1] = m[3][2] = m[0][3] = m[1][3] = m[2][3] = 0.0f;
	m[3][3] = 1.0f;

	return m;

}

void Quaternion::setValue(const Vector3 &axis, float theta) {

	float sqnorm = DotProduct( axis, axis);

	if (sqnorm == 0.0f)
	{
		// axis too small.
		array[0] = array[1] = array[2] = 0.0f;
		array[3] = 1.0f;
	}
	else
	{
		theta *= 0.5f;
		float sin_theta = sinf(DegToRad(theta));

		if (sqnorm != 1.0f)
			sin_theta /= sqrt(sqnorm);

		array[0] = sin_theta * axis.x();
		array[1] = sin_theta * axis.y();
		array[2] = sin_theta * axis.z();
		array[3] = cosf(DegToRad((theta)));
	}
	
}

void Quaternion::setValue(const Matrix4x4& m) {

	float tr, s;
	int i, j, k;
	const int nxt[3] = { 1, 2, 0 };

	tr = m[0][0] + m[1][1] + m[2][2];

	if (tr > 0.0f)
	{
		s = sqrt(tr + m[3][3]);
		array[3] = float(s * 0.5);
		s = float(0.5) / s;

		array[0] = float((m[1][2] - m[2][1]) * s);
		array[1] = float((m[2][0] - m[0][2]) * s);
		array[2] = float((m[0][1] - m[1][0]) * s);
	}
	else
	{
		i = 0;
		if (m[1][1] > m[0][0])
			i = 1;

		if (m[2][2] > m[i][i])
			i = 2;

		j = nxt[i];
		k = nxt[j];

		s = float(sqrt(m[i][j] - m[j][j] + m[k][k]) + float(1.0));

		array[i] = float(s * 0.5);
		s = float(0.5 / s);

		array[3] = (m[j][k] - m[k][j]) * s;
		array[j] = (m[i][j] + m[j][i]) * s;
		array[k] = (m[i][k] + m[k][i]) * s;
	}
	
}
