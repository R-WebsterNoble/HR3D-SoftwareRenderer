#include "StdAfx.h"
#include "Transformer.h"
#include "MatrixStack.h"


void Transformer::Transform(Transformations& transformations, const Model& model, const Camera& camera)
{
	// I construct a matrix capable of taking each vertice from the model cordanates to the required step in the pipeline
	// i do this to prevent rounding errors adding up

	Matrix3D matrix;
	matrix = model.GetTransformations() * matrix;
	matrix = camera.CameraTransform() * matrix;

	// we do this initial transform make sure the polygons are copied from the model
	InitialTransformation(transformations, model, matrix);

	//transform the normals in camera space
	transformations.TransformNormals(matrix);

	matrix = camera.PerspectiveProjection() * matrix;

	TransformTo(transformations.GetPerspective(), model, matrix);
	transformations.GetPerspective().Dehomogenize();

	matrix = camera.ScreenTransform() * matrix;

	TransformTo(transformations.GetScreen(), model, matrix);
	transformations.GetScreen().Dehomogenize();	
}

void Transformer::TransformTo(VertexBuffer& targetBuffer, const Model& sourceBuffer, const Matrix3D& matrix)
{
	int vertexCount = sourceBuffer.GetVertexCount();
	targetBuffer.SetVertexCount(vertexCount);
	Vertex* sourceVertices = sourceBuffer.GetVertices();
	Vertex* targetVertices = targetBuffer.GetVertices();
	for(int i = 0; i < vertexCount; i++)
	{
		targetVertices[i] = matrix * sourceVertices[i];
	}	
}

void Transformer::InitialTransformation(Transformations& transformations, const Model& model, const Matrix3D& viewMatrix)
{
	//copy across polygons
	int polycount = model.GetPolygonCount();
	transformations.SetPolygonCount(polycount);
	Polygon3D* sourcePolygons = model.GetPolygons();
	Polygon3D* targetPolygons = transformations.GetPolygons();
	for(int i = 0; i < polycount; i++)
	{
		targetPolygons[i] = sourcePolygons[i];
	}

	//stansform and copy verticies
	int vertexCount = model.GetVertexCount();
	transformations.GetView().SetVertexCount(vertexCount);
	Vertex* sourceVertices = model.GetVertices();
	Vertex* targetVertices = transformations.GetView().GetVertices();
	for(int i = 0; i < vertexCount; i++)
	{
		targetVertices[i] = viewMatrix * sourceVertices[i];
		//targetVertices[i].SetNormal(matrix * targetVertices[i].GetNormal());
	}	
}