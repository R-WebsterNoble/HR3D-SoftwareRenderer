#include "StdAfx.h"
#include "AmbientLight.h"

Colour AmbientLight::CalculatePolygonColour(Polygon3D& p, Vertex* vertices, Colour baseColour)
{
	return baseColour * _colour;
}

AmbientLight::AmbientLight(Colour colour)
{
	colour.Clamp();
	_colour = colour;
}

AmbientLight::~AmbientLight(void)
{
}
