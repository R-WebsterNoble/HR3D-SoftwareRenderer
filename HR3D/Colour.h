#pragma once
struct Colour
{
	Colour(float _r ,float _g ,float _b);

	Colour();

	Colour& operator+=(const Colour& rhs);

	Colour& operator*=(const float rhs);

	Colour operator+(const Colour& rhs) const;

	Colour operator*(const Colour& rhs) const;

	Colour operator+(const float rhs) const;

	void Clamp();

	float r, g, b;
};

