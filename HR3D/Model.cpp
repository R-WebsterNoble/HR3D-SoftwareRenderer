#include "StdAfx.h"
#include "Model.h"

void Model::Initialize(void)
{
	_vertices = NULL;
	_vertexCount = 0;

	_polygons = NULL;
	_polygonCount = 0;
}

Model::Model(void)
{
	Initialize();
}

Model::~Model(void)
{
	Cleanup();
}

void Model::Cleanup(void)
{
	delete [] _vertices;
	_vertexCount = 0;

	delete [] _polygons;
	_polygonCount = 0;
}

Vertex* Model::GetVertices(void) const
{
	return _vertices;
}

int Model::GetVertexCount(void) const
{
	return _vertexCount;
}

void Model::SetVertexCount(int count)
{
	if(_vertices != NULL)
		delete [] _vertices;

	_vertices = new Vertex[count];
	_vertexCount = count;
}

Polygon3D* Model::GetPolygons(void) const
{
	return _polygons;
}

int Model::GetPolygonCount(void) const
{
	return _polygonCount;
}

void Model::SetPolygonCount(int count)
{
	if(_polygons != NULL)
		delete [] _polygons;
	_polygons = new Polygon3D[count];
	_polygonCount = count;
}


const Matrix3D& Model::GetTransformations() const
{
	return _transformations;
}

void Model::SetTransformations(Matrix3D m)
{
	_transformations = m;
}

void Model::TransformNormals(const Matrix3D& matrix)
{
	for(int i = 0; i < _vertexCount; i++)
	{
		_vertices[i].SetNormal( matrix * _vertices[i].GetNormal());
	}

	for(int i = 0; i < _polygonCount; i++)
	{
		_polygons[i].faceNormal = matrix * _polygons[i].faceNormal;
	}
}

void Model::Dehomogenize()
{
	for(int i = 0; i < _vertexCount; i++)
	{
		_vertices[i].Dehomogenize();
	}
}

