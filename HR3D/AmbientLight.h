#pragma once
#include "light.h"
class AmbientLight :
	public Light
{
public:
	Colour CalculatePolygonColour(Polygon3D& p, Vertex* vertices, Colour baseColour);

	AmbientLight(Colour colour);
	~AmbientLight(void);

private:
	Colour _colour;
};

