#include "StdAfx.h"
#include "VertexBuffer.h"

void VertexBuffer::Initialize(void)
{
	_vertices = NULL;
	_vertexCount = 0;
}

VertexBuffer::VertexBuffer(void)
{
	Initialize();
}

VertexBuffer::~VertexBuffer(void)
{
	Cleanup();
}

void VertexBuffer::Cleanup(void)
{
	delete [] _vertices;
	_vertexCount = 0;
}

Vertex* VertexBuffer::GetVertices(void) const
{
	return _vertices;
}

int VertexBuffer::GetVertexCount(void) const
{
	return _vertexCount;
}

void VertexBuffer::SetVertexCount(int count)
{
	if(_vertices != NULL)
		delete [] _vertices;
	_vertices = new Vertex[count];
	_vertexCount = count;
}



void VertexBuffer::TransformNormals(const Matrix3D& matrix)
{
	for(int i = 0; i < _vertexCount; i++)
	{
		_vertices[i].SetNormal( matrix * _vertices[i].GetNormal());
	}
}

void VertexBuffer::Dehomogenize()
{
	for(int i = 0; i < _vertexCount; i++)
	{
		_vertices[i].Dehomogenize();
	}
}

