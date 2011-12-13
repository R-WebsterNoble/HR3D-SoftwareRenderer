#pragma once
#include "Vector3D.h"
#include "Vertex.h"

struct Polygon3D
{
	int verticesIndexes[3];
	Vector3D faceNormal;	

	void CalculateNormal(Vertex*);
};

