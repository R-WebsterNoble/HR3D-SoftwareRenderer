#pragma once
#include "Model.h"

class MD2Loader
{
	public:
		static bool LoadModel(const char* md2Filename, Model& model);
	private:
		MD2Loader(void);
		~MD2Loader(void);
};
