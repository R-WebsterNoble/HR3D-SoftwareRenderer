#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include "Colour.h"
class Light
{
public:
	Light(void);
	~Light(void);

	virtual Colour CalculatePolygonColour(Polygon3D& p, Vertex* vertices, Colour baseColour);
};

