#pragma once
#include "VertexBuffer.h"
class Transformations
{
public:

	Transformations(void);
	~Transformations(void);

	VertexBuffer& GetView();
	VertexBuffer& GetPerspective();
	VertexBuffer& GetScreen();

	Polygon3D* GetPolygons(void) const;
	int GetPolygonCount(void) const;
	void SetPolygonCount(int count);

	void TransformNormals(const Matrix3D& matrix);

	void PaintersSort();

	

private:
	VertexBuffer _view;
	VertexBuffer _perspective;
	VertexBuffer _screen;

	void Initialize(void);
	void Cleanup();

	Polygon3D* _polygons;
	int _polygonCount;

	void QSort(Polygon3D arr[], int beg, int end);	
};

