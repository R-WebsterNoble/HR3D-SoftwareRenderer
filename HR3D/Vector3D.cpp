#include "StdAfx.h"
#include "Vector3D.h"
#include <cmath>


Vector3D::Vector3D()
{
	Initialize();
}

Vector3D::Vector3D(const Vector3D &otherVec)
{
	for(int i = 0; i < SIZE; i++)
		_vector[i] = otherVec.GetAt(i);
}

Vector3D::Vector3D(float* vec)
{
	for(int i = 0; i < SIZE - 1; i++ )
	_vector[i] = vec[i];
	_vector[SIZE - 1] = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_vector[0] = x;
	_vector[1] = y;
	_vector[2] = z;
	_vector[3] = 1;
}

Vector3D::Vector3D(float x, float y, float z, float w)
{
	_vector[0] = x;
	_vector[1] = y;
	_vector[2] = z;
	_vector[3] = w;
}

void Vector3D::Initialize()
{
	for(int i = 0; i < SIZE; i++)
		_vector[i] = 0;
}

float Vector3D::GetAt(int i) const
{
	return _vector[i];
}

void Vector3D::SetAt(int i,float value)
{
	_vector[i] = value;
}

float Vector3D::GetX() const
{
	return _vector[0];
}

float Vector3D::GetY() const
{
	return _vector[1];
}

float Vector3D::GetZ() const
{
	return _vector[2];
}

float Vector3D::GetW() const
{
	return _vector[3];
}

void Vector3D::SetX(float value)
{
	_vector[0] = value;
}

void Vector3D::SetY(float value)
{
	_vector[1] = value;
}

void Vector3D::SetZ(float value)
{
	_vector[2] = value;
}

void Vector3D::SetW(float value)
{
	_vector[3] = value;
}

Vector3D& Vector3D::Normalise()
{
	float dist = sqrt( (_x * _x)+(_y * _y)+(_z * _z) );
	
	_x = _x * ( 1.0 / dist );
	_y = _y * ( 1.0 / dist );
	_z = _z * ( 1.0 / dist );

	return * this;
}

float Vector3D::DotProduct(const Vector3D& v1, const Vector3D& v2)
{
	return (v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY() + v1.GetZ() * v2.GetZ());
}

Vector3D Vector3D::CrossProduct(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY(),
					v1.GetZ() * v2.GetX() - v1.GetX() * v2.GetZ(),
					v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX(),
					0);
}