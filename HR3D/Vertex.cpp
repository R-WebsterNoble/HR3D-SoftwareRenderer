#include "StdAfx.h"
#include "Vertex.h"

// Constructors

Vertex::Vertex(void)
{
	Init(0.0f, 0.0f, 0.0f, 1);
}

Vertex::Vertex(float x, float y, float z, float w)
{
	Init(x, y, z, w);
}

Vertex::~Vertex(void)
{
}

Vector3D Vertex::ToVector3D() const
{
	Vector3D v(_x,_y,_z);
	return v;
}

// Accessors and mutators

float Vertex::GetX(void) const
{
	return _x;
}

void Vertex::SetX(float x)
{
	_x = x;
}

float Vertex::GetY(void) const
{
	return _y;
}

void Vertex::SetY(float y)
{
	_y = y;
}

float Vertex::GetZ(void) const
{
	return _z;
}

void Vertex::SetZ(float z)
{
	_z = z;
}

float Vertex::GetW(void) const
{
	return _w;
}

void Vertex::SetW(float w)
{
	_w = w;
}

float Vertex::GetAt(int i) const
{
	return _vec[i];
}

void Vertex::SetAt(int i,float value)
{
	_vec[i] = value;
}

Vector3D Vertex::GetNormal()
{
	return _normal;
}

void Vertex::SetNormal(Vector3D normal)
{
	_normal = normal;
}

// Operator overloads

Vertex Vertex::operator+ (const Vertex &rhs)
{
	Vertex result;
	result._x = _x + rhs._x;
	result._y = _y + rhs._y;
	result._z = _z + rhs._z;
	return result;
}

void Vertex::Dehomogenize()
{
	_x /= _w;
	_y /= _w;
	_z /= _w;
	_w = 1;
}

// Private methods

void Vertex::Init(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}


