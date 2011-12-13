#include "StdAfx.h"
#include "Transformations.h"


VertexBuffer& Transformations::GetView()
{
	return _view;
}

VertexBuffer& Transformations::GetPerspective()
{
	return _perspective;
}

VertexBuffer& Transformations::GetScreen()
{
	return _screen;
}

Polygon3D* Transformations::GetPolygons(void) const
{
	return _polygons;
}

int Transformations::GetPolygonCount(void) const
{
	return _polygonCount;
}

void Transformations::SetPolygonCount(int count)
{
	if(_polygons != NULL)
		delete [] _polygons;
	_polygons = new Polygon3D[count];
	_polygonCount = count;
}

 Transformations::Transformations(void)
 {
	 Initialize();
 }

 Transformations::~Transformations(void)
 {
	 Cleanup();
 }

void Transformations::Initialize()
{
	_polygons = NULL;
	_polygonCount = 0;
}

void Transformations::Cleanup()
{
	delete [] _polygons;
	_polygonCount = 0;
}

void Transformations::TransformNormals(const Matrix3D& matrix)
{
	//we only ever use the normals in the view transformation (camera space) to transform them
	_view.TransformNormals(matrix);

	for(int i = 0; i < _polygonCount; i++)
	{
		_polygons[i].faceNormal = matrix * _polygons[i].faceNormal;

		// we must normalise the normals
		_polygons[i].faceNormal.Normalise();
	}
}

void Transformations::PaintersSort()
{
	QSort(_polygons, 0, _polygonCount);
}

inline void swap(Polygon3D *a, Polygon3D *b)
{
  Polygon3D t=*a; *a=*b; *b=t;
}

void Transformations::QSort(Polygon3D arr[], int beg, int end)
{
  if (end > beg + 1)
  {
	Polygon3D* piv = &arr[beg];

    int l = beg + 1, r = end;

    while (l < r)
    {
		Vertex* v = _perspective.GetVertices();
		//adverage z across 3 verticies to get middle of polygon to use for comparison
		// use this midpoint for the comparison for the sort
		if (v[arr[l].verticesIndexes[0]].GetZ() +
			v[arr[l].verticesIndexes[1]].GetZ() + 
			v[arr[l].verticesIndexes[2]].GetZ() / 3 <=
			v[piv->verticesIndexes[0]  ].GetZ()+
			v[piv->verticesIndexes[1]  ].GetZ()+
			v[piv->verticesIndexes[2]  ].GetZ() / 3)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[beg]);
    QSort(arr, beg, l);
    QSort(arr, r, end);
  }
}
