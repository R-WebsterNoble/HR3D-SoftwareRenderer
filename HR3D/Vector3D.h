#pragma once

#include <GdiPlus.h>
#include "Vector3D.h"

#define SIZE 4

class Vector3D
{
public:
	Vector3D();
	Vector3D(const Vector3D&);
	Vector3D(float*);
	Vector3D(float, float, float);
	Vector3D(float, float, float, float);

	static float DotProduct(const Vector3D&, const Vector3D&);

	static Vector3D CrossProduct(const Vector3D&, const Vector3D&);	

	Vector3D& Normalise();

	float GetAt(int) const;
	void SetAt(int, float);	

	float GetX() const;
	void SetX(float);

	float GetY() const;
	void SetY(float);

	float GetZ() const;
	void SetZ(float);

	float GetW() const;
	void SetW(float);

private:

	union 
	{
		struct 
		{
			float _x, _y, _z, _w;
		}; 
		float _vector[SIZE];
	}; 

	void Vector3D::Initialize();
};

