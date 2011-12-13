#pragma once
#include "VertexBuffer.h"
#include "Model.h"
#include "Transformations.h"
#include "Camera.h"
#include "Matrix3D.h"

class Transformer
{
public:
	static void Transform(Transformations& outTransformations, const Model& model, const Camera& camera);

private:
	static void TransformTo(VertexBuffer& targetBuffer, const Model& sourceBuffer, const Matrix3D& matrix);
	static void InitialTransformation(Transformations& transformations, const Model& sourceBuffer, const Matrix3D& viewMatrix);
};

