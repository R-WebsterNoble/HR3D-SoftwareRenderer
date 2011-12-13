#include "StdAfx.h"
#include "Polygon3D.h"
#include "Vector3D.h"

void Polygon3D::CalculateNormal(Vertex* vertices)
{
	//calculate face normal


	//cache vertivies to prevent multiple lookups
	Vertex v0 = vertices[verticesIndexes[0]];
	Vertex v1 = vertices[verticesIndexes[1]];
	Vertex v2 = vertices[verticesIndexes[2]];

	Vector3D u(v2.GetX() - v0.GetX(),
				v2.GetY() - v0.GetY(),
				v2.GetZ() - v0.GetZ());

	Vector3D v(v2.GetX() - v1.GetX(),
				v2.GetY() - v1.GetY(),
				v2.GetZ() - v1.GetZ());

	Vector3D n = Vector3D::CrossProduct(u,v);

	faceNormal.SetX(u.GetY() * v.GetZ() - u.GetZ() * v.GetY());
	faceNormal.SetY(u.GetZ() * v.GetX() - u.GetX() * v.GetZ());
	faceNormal.SetZ(u.GetX() * v.GetY() - u.GetY() * v.GetX());
}

