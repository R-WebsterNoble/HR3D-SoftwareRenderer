#include "StdAfx.h"
#include "Rasterizer.h"
#include "Polygon3D.h"

Rasterizer::Rasterizer(void)
{
	// Declared private so should not be called.
	_bitmap = NULL;
	_graphics = NULL;
}

Rasterizer::Rasterizer(unsigned int width, unsigned int height)
{
	// Create a bitmap of the specified size and get a reference to the graphics object
	// for that bitmap. Note that these calls could theoretically fail so we really should
	// handle that, but we will leave that for now. 
	_width = width;
	_height = height;
	_bitmap = new Bitmap(_width, _height, PixelFormat32bppARGB);
	_graphics = new Graphics(_bitmap);
}

Rasterizer::~Rasterizer(void)
{
	// Clean up all dynamically created objects
	if (_graphics)
	{
		delete _graphics;
		_graphics = NULL;
	}
	if (_bitmap)
	{
		delete _bitmap;
		_bitmap = NULL;
	}
}

// Accessors

unsigned int Rasterizer::GetWidth() const
{
	return _width;
}

unsigned int Rasterizer::GetHeight() const
{
	return _height;
}

Bitmap * Rasterizer::GetBitmap() const
{
	return _bitmap;
}

// Clear the bitmap using the specified colour

void Rasterizer::Clear(const Color& color)
{
	if (_graphics)
	{
		_graphics->Clear(color);
	}
}

void Rasterizer::DrawTextToScreen(WCHAR* string, int stringLength)
{
	if (_graphics)
	{
		// Initialize arguments.
		Font myFont(L"Arial", 12);
		PointF origin(0.0f, 0.0f);
		SolidBrush blackBrush(Color(255, 0, 0, 0));

		_graphics->DrawString(
		   string,
		   stringLength,
		   &myFont,
		   origin,
		   &blackBrush);
	}
}

void Rasterizer::DrawFlat(Transformations& transformations, std::vector<Light*> lights, Colour reflectance)
{
	//cache screen vertex buffer
	VertexBuffer* screen = &transformations.GetScreen();

	//cache verticies array
	Vertex* verticies = screen->GetVertices();

	//cache count
	int count = transformations.GetPolygonCount();
	for(int i = 0; i < count; i++)
	{		
		//cache polygon
		Polygon3D* polygon = &(transformations.GetPolygons()[i]);

		//cache cullVertex
		Vertex* cullVertex = &transformations.GetView().GetVertices()[polygon->verticesIndexes[0]];


		//backfase culling is done here:
		if(Vector3D::DotProduct(cullVertex->ToVector3D(), polygon->faceNormal)<0)
		{
			//cache projectionVertices
			Vertex* projectionVertices = transformations.GetPerspective().GetVertices();

			Vertex pv0 = projectionVertices[polygon->verticesIndexes[0]];
			Vertex pv1 = projectionVertices[polygon->verticesIndexes[1]];
			Vertex pv2 = projectionVertices[polygon->verticesIndexes[2]];

			//this is fustrum cullling
			// the projection matrix i use transforms the z coordanates i can use this to check if the vertice is outside the near or far clipping planes
			// if non of the verticies are within the view fustrum on 1 axis dont draw the polygon
			if(!(pv0.GetX() < -1 || pv0.GetX() > 1 || pv0.GetY() < -1 || pv0.GetY() > 1  ||  pv0.GetZ() < 1 ) ||
				!(pv1.GetX() < -1 || pv1.GetX() > 1 || pv1.GetY() < -1 || pv1.GetY() > 1  ||  pv1.GetZ() < 1 ) || 
				!(pv2.GetX() < -1 || pv2.GetX() > 1 || pv2.GetY() < -1 || pv2.GetY() > 1 || pv2.GetZ() < 1))
			{	
				Vertex v0 = verticies[polygon->verticesIndexes[0]];
				Vertex v1 = verticies[polygon->verticesIndexes[1]];
				Vertex v2 = verticies[polygon->verticesIndexes[2]];

				Gdiplus::PointF poly[3];

				Gdiplus::PointF point0(v0.GetX(), v0.GetY());
				Gdiplus::PointF point1(v1.GetX(), v1.GetY());
				Gdiplus::PointF point2(v2.GetX(), v2.GetY());

				poly[0] = point0;
				poly[1] = point1;
				poly[2] = point2;

				int count = lights.size();
				Colour colour;
				//loop throught every light
				for(int i = 0; i < count; i++)
				{
					//add the colour generated at this point to the total colour
					colour += lights[i]->CalculatePolygonColour(*polygon,verticies,reflectance);

					//clamp to prevent overflow or -lights
					colour.Clamp();
				}

				SolidBrush pen(Color((BYTE)(colour.r * 255), (BYTE)(colour.g * 255), (BYTE)(colour.b * 255)));

				//draw the polygon
				_graphics->FillPolygon(&pen, poly, 3);
			}
		}
	}
}

void Rasterizer::DrawWireFrame(Transformations& transformations, Gdiplus::Color colour)
{
	VertexBuffer* screen = &transformations.GetScreen();

	Vertex* verticies = screen->GetVertices();
	int count = transformations.GetPolygonCount();
	for(int i = 0; i < count; i++)
	{		
		Polygon3D* polygon = &(transformations.GetPolygons()[i]);

		Vertex* cullVertex = &transformations.GetView().GetVertices()[polygon->verticesIndexes[0]];


		if(Vector3D::DotProduct(cullVertex->ToVector3D(), polygon->faceNormal)<0)
		{
			Vertex* projectionVertices = transformations.GetPerspective().GetVertices();

			Vertex pv0 = projectionVertices[polygon->verticesIndexes[0]];
			Vertex pv1 = projectionVertices[polygon->verticesIndexes[1]];
			Vertex pv2 = projectionVertices[polygon->verticesIndexes[2]];


			//this is fustrum cullling
			// the projection matrix i use transforms the z coordanates i can use this to check if the vertice is outside the near or far clipping planes
			// if non of the verticies are within the view fustrum on 1 axis dont draw the polygon

			if(!(pv0.GetX() < -1 || pv0.GetX() > 1 || pv0.GetY() < -1 || pv0.GetY() > 1  ||  pv0.GetZ() < 1 ) ||
				!(pv1.GetX() < -1 || pv1.GetX() > 1 || pv1.GetY() < -1 || pv1.GetY() > 1  ||  pv1.GetZ() < 1 ) || 
				!(pv2.GetX() < -1 || pv2.GetX() > 1 || pv2.GetY() < -1 || pv2.GetY() > 1 || pv2.GetZ() < 1))
			{	
				Vertex v0 = verticies[polygon->verticesIndexes[0]];
				Vertex v1 = verticies[polygon->verticesIndexes[1]];
				Vertex v2 = verticies[polygon->verticesIndexes[2]];

				//make an array to cold the points
				Gdiplus::PointF poly[3];

				Gdiplus::PointF point0(v0.GetX(), v0.GetY());
				Gdiplus::PointF point1(v1.GetX(), v1.GetY());
				Gdiplus::PointF point2(v2.GetX(), v2.GetY());

				poly[0] = point0;
				poly[1] = point1;
				poly[2] = point2;
				
				Pen pen(colour);

				//draw the polygon
				_graphics->DrawPolygon(&pen, poly, 3);
			}
		}
	}
}


