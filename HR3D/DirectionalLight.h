#pragma once
#include "light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(Colour c, Vector3D v);
	~DirectionalLight(void);

	Colour CalculatePolygonColour(Polygon3D& p, Vertex* vertices, Colour baseColour);
private:
	Colour _colour;
	Vector3D _direction;
};

