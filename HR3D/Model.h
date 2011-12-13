#pragma once
#include "Vertex.h"
#include "Polygon3D.h"
#include "Matrix3D.h"

class Model
{
public:
	Model(void);
	Model(const Model&, const Matrix3D&);
	~Model(void);

	Vertex* GetVertices(void) const;
	int GetVertexCount(void) const;
	void SetVertexCount(int count);

	Polygon3D* GetPolygons(void) const;
	int GetPolygonCount(void) const;
	void SetPolygonCount(int count);

	const Matrix3D& GetTransformations() const;
	void SetTransformations(Matrix3D);

	void TransformNormals(const Matrix3D&);
	void Dehomogenize();

private:
	Vertex* _vertices;
	int _vertexCount;

	Matrix3D _transformations;

	Polygon3D* _polygons;
	int _polygonCount;

	void Initialize(void);

	void Cleanup(void);
};

