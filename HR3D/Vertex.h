#pragma once
#include "Vector3D.h"

// Class representing a 3D vertex (i.e a point in 3 dimensional space)
class Vertex
{
	public:
		Vertex(void);
		Vertex(float x, float y, float z, float w);
		~Vertex(void);

		float GetX(void) const;
		void SetX(float x);
		float GetY(void) const;
		void SetY(float y);
		float GetZ(void) const;
		void SetZ(float y);
		float GetW(void) const;
		void SetW(float y);

		float GetAt(int) const;
		void SetAt(int, float);

		void Dehomogenize();

		Vector3D GetNormal();
		void SetNormal(Vector3D);

		Vector3D ToVector3D() const;

		Vertex operator+ (const Vertex &rhs);

	private:

		union {
			struct {
				float _x, _y, _z, _w;
			}; 
			float _vec[4];
		}; 

		Vector3D _normal;

		void Init(float x, float y, float z, float w);
};

