#pragma once
#include "Vertex.h"
#include "Transformations.h"
#include "Light.h"
#include "Colour.h"
#include <vector>

using namespace Gdiplus;

class Rasterizer
{
	public:
		Rasterizer(unsigned int width, unsigned int height);
		~Rasterizer(void);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		Bitmap* GetBitmap() const;

		void Rasterizer::DrawFlat(Transformations& transformations, std::vector<Light*> lights, Colour reflectance);
		void Rasterizer::DrawWireFrame(Transformations& transformations, Gdiplus::Color colour);

		void Clear(const Color& color);
		void DrawTextToScreen(WCHAR* string, int stringLength);

	private:
		unsigned int _width;
		unsigned int _height;
		Bitmap * _bitmap;
		Graphics * _graphics; 

		// Private constructor. Should not be used directly.
		Rasterizer(void);
};

