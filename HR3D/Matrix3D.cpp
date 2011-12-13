#include "StdAfx.h"
#include "Matrix3D.h"
#include "Vector3D.h"
#include <cmath>



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


Matrix3D::Matrix3D()
{
	for(int c = 0; c < COLS; c++)
		for(int r = 0; r < ROWS; r++)		
			_matrix[c][r] = ((c == r)?1.0f:0.0f); // identity matrix		
}

Matrix3D::Matrix3D(const Matrix3D& otherMatrix)
{
	for(int c = 0; c < COLS; c++)
		for(int r = 0; r < ROWS; r++)
			_matrix[c][r] = otherMatrix._matrix[c][r];
}

Matrix3D Matrix3D::CreateRotation(float x, float y, float z)
{
	return CreateRotationX(x) * CreateRotationY(y) * CreateRotationZ(z);
}

Matrix3D Matrix3D::CreateRotationX(float r)
{
	Matrix3D result;

	result._matrix[1][1] = //cos(r)
	result._matrix[2][2] = cos(r);

	result._matrix[2][1] = -//sin(r)
	(result._matrix[1][2] = sin(r));

	return result;
}

Matrix3D Matrix3D::CreateRotationY(float r)
{
	Matrix3D result;

	result._matrix[0][0] = //cos(r)
	result._matrix[2][2] = cos(r);

	result._matrix[0][2] = -//sin(r)
	(result._matrix[2][0]= sin(r));
	return result;
}

Matrix3D Matrix3D::CreateRotationZ(float r)
{
	Matrix3D result;

	result._matrix[0][0] = //cos(r)
	result._matrix[1][1] = cos(r);

	result._matrix[1][0] = -//sin(r)
	(result._matrix[0][1]= sin(r));
	return result;
}

Matrix3D Matrix3D::CreateTranslation(float x, float y, float z)
{
	Matrix3D result;
	result._matrix[3][0] = x;
	result._matrix[3][1] = y;
	result._matrix[3][2] = z;
	return result;
}

Matrix3D Matrix3D::CreateTranslation(Vector3D pos)
{
	Matrix3D result;
	result._matrix[3][0] = pos.GetX();
	result._matrix[3][1] = pos.GetY();
	result._matrix[3][2] = pos.GetZ();
	return result;
}

Matrix3D Matrix3D::CreateScale(float x, float y, float z)
{
	Matrix3D result;
	result._matrix[0][0] = x;
	result._matrix[1][1] = y;
	result._matrix[2][2] = z;
	return result;
}

Matrix3D Matrix3D::CreateScale(Vector3D s)
{
	Matrix3D result;
	result._matrix[0][0] = s.GetX();
	result._matrix[1][1] = s.GetY();
	result._matrix[2][2] = s.GetZ();

	return result;
}

Matrix3D Matrix3D::CreatePerspectiveProjection(float fov,float aspect, float zNear, float zFar)
{
	Matrix3D result;

	float cot = tanf(3.14159265f/2.0f - (fov / 2));

	result._matrix[0][0] = cot / aspect;

	result._matrix[1][1] = cot;

	result._matrix[2][2] = (zFar + zNear) / (zNear - zFar);

	result._matrix[3][2] = (2 * zFar * zNear) / (zNear - zFar);

	result._matrix[2][3] = -1;
	result._matrix[3][3] = 0;

	return result;
}

float Matrix3D::Get(int c, int r) const
{
	return _matrix[c][r];
}

void Matrix3D::Set(int c, int r, float value)
{
	_matrix[c][r] = value;
}

Matrix3D& Matrix3D::operator= (const Matrix3D &rhs)
{
	Matrix3D result;
	for(int c = 0; c < COLS; c++)
		for(int r = 0; r < ROWS; r++)
			_matrix[c][r] = rhs._matrix[c][r];
	return *this;
}

Matrix3D& Matrix3D::operator*=(const Matrix3D &rhs)
{
	Matrix3D copy = *this;//create a copy
	for(int c = 0; c < COLS; c++)
		for(int r = 0; r < ROWS; r++)
		{
			float cellTotal = 0;

			for(int i = 0; i < COLS; i++)
			{
				cellTotal += copy._matrix[i][r] * rhs._matrix[c][i];				
			}
			_matrix[c][r] = cellTotal;
		}

	return *this;
}

Matrix3D Matrix3D::operator*(const Matrix3D &rhs) const
{
	Matrix3D result;
	for(int c = 0; c < COLS; c++)
		for(int r = 0; r < ROWS; r++)
		{
			float cellTotal = 0;

			for(int i = 0; i < COLS; i++)
			{
				cellTotal += _matrix[i][r] * rhs._matrix[c][i];				
			}
			result._matrix[c][r] = cellTotal;
		}
	return result;
}

Vector3D Matrix3D::operator*(const Vector3D &rhs) const
{
	Vector3D result;
	for(int r = 0; r < ROWS; r++)
	{
		float cellTotal = 0;

		for(int i = 0; i < ROWS; i++)
		{
			cellTotal += _matrix[i][r] * rhs.GetAt(i);				
		}

		result.SetAt(r, cellTotal);
	}
	return result;
}

Vertex Matrix3D::operator*(const Vertex &rhs) const
{
	Vertex result;
	for(int r = 0; r < ROWS; r++)
	{
		float cellTotal = 0;

		for(int i = 0; i < ROWS; i++)
		{
			cellTotal += _matrix[i][r] * rhs.GetAt(i);				
		}
		result.SetAt(r, cellTotal);
	}
	return result;
}
