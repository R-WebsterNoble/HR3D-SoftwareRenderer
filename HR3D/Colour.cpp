#include "StdAfx.h"
#include "Colour.h"
#include <algorithm>

Colour::Colour(float _r ,float _g ,float _b)
{
	r = _r;
	g = _g;
	b = _b;
}

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
}

Colour& Colour::operator+=(const Colour& rhs)
{
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;
	return *this;
}

Colour& Colour::operator*=(const float rhs)
{
	r *= rhs;
	g *= rhs;
	b *= rhs;
	return *this;
}

Colour Colour::operator+(const Colour& rhs) const
{
	Colour result;

	result.r = r + rhs.r;
	result.g = g + rhs.g;
	result.b = b + rhs.b;

	return result;
}

Colour Colour::operator*(const Colour& rhs) const
{
	Colour result;

	result.r = r * rhs.r;
	result.g = g * rhs.g;
	result.b = b * rhs.b;

	return result;
}

Colour Colour::operator+(const float rhs) const
{
	Colour result;
	
	result.r = r + rhs;
	result.g = g + rhs;
	result.b = b + rhs;

	return result; 
}

void Colour::Clamp()
{
	r = max(0.0f, min(r, 1.0f));
	g = max(0.0f, min(g, 1.0f));
	b = max(0.0f, min(b, 1.0f));
}

