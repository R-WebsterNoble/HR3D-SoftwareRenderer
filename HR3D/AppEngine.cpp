#include "StdAfx.h"
#include "AppEngine.h"
#include <cmath>
#include "VertexBuffer.h"
#include "MD2Loader.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "Transformations.h"
#include "Transformer.h"
#include "MatrixStack.h"

#define MODEL_FILENAME "Ogros.md2"
#define MODEL2_FILENAME "marvin.md2"
//#define MODEL_FILENAME "Cube.md2"

// Main 'engine' class for our application. This is where all of the core processing work is done

AppEngine::AppEngine(void)
{
	_rasterizer = NULL;
}

AppEngine::~AppEngine(void)
{
	// Make sure everything is cleaned up (in case Shutdown() was now called directly
	Shutdown();
}

void AppEngine::Initialise(HWND hWnd)
{
	_hWnd = hWnd;
	
	// Get the width and height of the window so that we can tell the rasterizer to create a bitmap
	// of the same size.  Note that this only works for the initial size of the window. If you want 
	// your code to handle resizing of the window, you will need to add code for this yourself. 
	LONG width;
	LONG height;
	RECT clientWindowRect;
	if (GetClientRect(_hWnd, &clientWindowRect))
	{
		width = clientWindowRect.right;
		height = clientWindowRect.bottom;
	}
	else
	{
		width = 640;
		height = 480;
	}

	//create rasteriser
	_rasterizer = new Rasterizer((unsigned int)width, (unsigned int)height);

	//setup camera
	camera = Camera(Vector3D(),Vector3D(0,0,-50), width, height);	

	//load models
	MD2Loader::LoadModel(MODEL_FILENAME, _model);
	MD2Loader::LoadModel(MODEL2_FILENAME, _model2);

}

float rotation = 0;
int frameCounter = 0;
WCHAR* text;
int textLength;

void AppEngine::Process(void)
{
	BeginRender();

	rotation += 0.0104719755119659774f;	

	if(frameCounter == 0)
	{
		text = L"Wireframe \nModel Rotation \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 84;
	}
	else if (frameCounter == 500)
	{
		text = L"Flat Shading \nNo Lights \nModel Rotation \nModel Rotation \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 114;
	}
	else if (frameCounter == 1000)
	{
		_lights.push_back(new AmbientLight(Colour(1,0,0)));

		text = L"Flat Shading \nRed Ambient light only \nModel Rotation \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 111;
	}
	else if (frameCounter == 1500)
	{
		_lights.pop_back();
		_lights.push_back(new DirectionalLight(Colour(1,0,0), Vector3D(1,0,0)));

		text = L"Flat Shading \nRed Directional light only \nModel Rotation \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 115;
	}
	else if (frameCounter == 2000)
	{
		_lights.push_back(new AmbientLight(Colour(0,0.2f,0)));
		_lights.push_back(new DirectionalLight(Colour(1,0,0), Vector3D(1,0,0)));

		text = L"Flat Shading \nRed Directional light and Green Ambient Light \nModel Rotation \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 134;
	}
	else if (frameCounter == 2500)
	{
		text = L"Camera Rotation \nFlat Shading \nRed Directional light and Green Ambient Light \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 135;
	}
	else if (frameCounter == 3000)
	{
		text = L"Multiple Models with Diffrent Trasnsformations \nUsing Matrix Stack \nFlat Shading \nRed Directional light and Green Ambient Light \nBackface Culling \nFustrum Culling \nPerspective Projection";
		textLength = 186;
		camera.SetRotation(Vector3D(0,0,0));
	}
	else if(frameCounter == 3500)
	{
		//reset everything
		frameCounter = 0;
		rotation = 0;


		//delete lights
		for(unsigned int i = 0; i < _lights.size(); i++)
		{
			delete _lights[i];
		}
		_lights.clear();
	}


	if (frameCounter >= 2500 && frameCounter < 3000)
	{
		//rotate camera
		camera.SetRotation(Vector3D(0,rotation * 2,0));
		_model.SetTransformations(Matrix3D::CreateRotationY(1.5));
	}
	else 
	{
		_model.SetTransformations(Matrix3D::CreateRotation(rotation, rotation * 0.83454f, rotation * 1.3464f));
		if (frameCounter >= 3000)
		{
			// construct matrix stack and rander models as we go along
			MatrixStack matrixStack;

			matrixStack.Push( Matrix3D::CreateRotation(0,rotation,0));
			_model2.SetTransformations(matrixStack.Peek());
			RenderModel(_model2);

			matrixStack.Push( Matrix3D::CreateTranslation(40,0,0));
			matrixStack.Push( Matrix3D::CreateRotation(0,rotation * 2,0));	
			_model2.SetTransformations(matrixStack.Peek());
			RenderModel(_model2);

			matrixStack.Push( Matrix3D::CreateTranslation(30,0,0));
			matrixStack.Push( Matrix3D::CreateRotation(0,rotation * 3,0));	
			_model2.SetTransformations(matrixStack.Peek());
			RenderModel(_model2);

			matrixStack.Push( Matrix3D::CreateTranslation(20,0,0));
			matrixStack.Push( Matrix3D::CreateRotation(0,3.2f,0));	
			_model.SetTransformations(matrixStack.Peek());
		}
	}

	//render the model
	RenderModel(_model);

	frameCounter++;

	EndRender();

}

void AppEngine::RenderModel(Model& model)
{	
	Transformations transformations;

	Transformer::Transform(transformations, model, camera);	
	
	

	if(frameCounter < 500)
	{
		_rasterizer->DrawWireFrame(transformations, Gdiplus::Color(1,1,1));
		//_rasterizer->DrawText(L"s", 1000);
	}
	else //if(frameCounter < 1000)
	{
		//we must use a z-depth sort otherwise the polygons dont aear in the right z order
		//this is not needed for wireframe
		transformations.PaintersSort();
		_rasterizer->DrawFlat(transformations, _lights, Colour(1,1,1));		
	}	

}

void AppEngine::BeginRender()
{
	_rasterizer->Clear(Color::LightGray);
}

void AppEngine::EndRender()
{
	_rasterizer->DrawTextToScreen(text, textLength);

	// Ensure that Windows is told that the contents of the window now needs painting
	InvalidateRect(_hWnd, NULL, FALSE);
}

void AppEngine::Paint(HDC hdc)
{
	// Copy the contents of the rasterizer's bitmap to our window
	if (_rasterizer)
	{
		Graphics graphics(hdc);
		graphics.DrawImage(_rasterizer->GetBitmap(), 0, 0, _rasterizer->GetWidth(), _rasterizer->GetHeight());
	}
}

void AppEngine::Shutdown(void)
{
	// Clean up all memory that has been dynamically allocated
	if (_rasterizer)
	{
		delete _rasterizer;
		_rasterizer = NULL;
	}

	for(unsigned int i = 0; i < _lights.size(); i++)
	{
		delete _lights[i];
	}
}