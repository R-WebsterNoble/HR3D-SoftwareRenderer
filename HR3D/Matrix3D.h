#pragma once
#include "StdAfx.h"
#include "Vector3D.h"
#include <GdiPlus.h>
#include "Vertex.h"

#define COLS 4
#define ROWS 4

/*
x1, x2, x3, x4,
y1, y2, y3, y4,
z1, z2, z3, z4,
w1, w2, w3, w4

[0,0][1,0][2,0][3,0]
[0,1][1,1][2,1][3,1]
[0,2][1,2][2,2][3,2]
[0,3][1,3][2,3][3,3]
*/

class Matrix3D
{
	private:
		float _matrix[COLS][ROWS];
	public:
		Matrix3D(void);
		Matrix3D(const Matrix3D&);

		static Matrix3D CreateRotation(float, float, float);
		static Matrix3D CreateRotationX(float);
		static Matrix3D CreateRotationY(float);
		static Matrix3D CreateRotationZ(float);
		static Matrix3D CreateTranslation(float, float, float);
		static Matrix3D CreateTranslation(Vector3D);
		static Matrix3D CreateScale(float, float, float);
		static Matrix3D CreateScale(Vector3D);

		static Matrix3D Matrix3D::CreatePerspectiveProjection(float fov,float aspect, float zNear, float zFar);

		float Get(int, int) const;
		void Set(int, int, float);

		Matrix3D& operator= (const Matrix3D&);

		Matrix3D& operator*=(const Matrix3D&);

		Matrix3D operator*(const Matrix3D&) const;
		Vector3D operator*(const Vector3D&) const;
		Vertex operator*(const Vertex&) const;	
};
