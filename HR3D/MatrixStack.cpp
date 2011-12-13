#include "StdAfx.h"
#include "MatrixStack.h"


MatrixStack::MatrixStack(void)
{
	Matrix3D m;

	_matrixStack.push_back(m);
}

Matrix3D& MatrixStack::Push(const Matrix3D& matrix)
{
	//multiply the new matrix with the one op top of the stack
	Matrix3D result =  _matrixStack.back()  * matrix;

	//save the result
	_matrixStack.push_back(result);
	return result;
}

void MatrixStack::Pop()
{
	_matrixStack.pop_back();
}

Matrix3D& MatrixStack::Peek()
{
	return _matrixStack.back();
}
