#include "StdAfx.h"
#include "DirectionalLight.h"

Colour DirectionalLight::CalculatePolygonColour(Polygon3D& p, Vertex* vertices, Colour baseColour)
{
	// multiply like ambient light
	Colour result = baseColour * _colour;

	//this makes the light directional
	float dp = Vector3D::DotProduct(_direction, p.faceNormal);
	result *= dp;

	return result;
}

DirectionalLight::DirectionalLight(Colour c, Vector3D v)
{
	c.Clamp();
	_colour = c;
	_direction = v;

	//light vector must be normalised
	_direction.Normalise();
}


DirectionalLight::~DirectionalLight(void)
{
}
