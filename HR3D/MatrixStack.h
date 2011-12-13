#pragma once
#include <vector>
#include "Matrix3D.h"

class MatrixStack
{
public:
	MatrixStack(void);

	Matrix3D& Push(const Matrix3D&);
	void Pop();
	Matrix3D& Peek();

private:
	std::vector<Matrix3D> _matrixStack;
};

