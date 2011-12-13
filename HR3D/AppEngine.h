#pragma once
#include "Rasterizer.h"
#include "Model.h"
#include "Camera.h"
#include <vector>
#include "Light.h"

class AppEngine
{	
private:
		HWND _hWnd;
		Rasterizer* _rasterizer;
		Model _model;
		Model _model2;
		std::vector<Light*> _lights;

		Camera camera;

		void RenderModel(Model& model);
		void BeginRender();
		void EndRender();


	public:
		AppEngine(void);
		~AppEngine(void);

		void Initialise(HWND hWnd);
		void Process(void);
		void Paint(HDC hdc);
		void Shutdown(void);
};

