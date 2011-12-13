#pragma once
#include "Vertex.h"
#include "Polygon3D.h"
#include "Matrix3D.h"

class VertexBuffer
{
public:
	VertexBuffer(void);
	VertexBuffer(const VertexBuffer&, const Matrix3D&);
	~VertexBuffer(void);

	Vertex* GetVertices(void) const;
	int GetVertexCount(void) const;
	void SetVertexCount(int count);

	void TransformNormals(const Matrix3D&);
	void Dehomogenize();

	void Sort();

private:
	Vertex* _vertices;
	int _vertexCount;

	void Initialize(void);

	void Cleanup(void);
};

