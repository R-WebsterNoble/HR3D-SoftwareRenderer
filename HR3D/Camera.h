#pragma once

#include "Vector3D.h"
#include "Matrix3D.h"

class Camera
{
private:
	Vector3D _rotation;
	Vector3D _position;
	unsigned int _viewWidth;
	unsigned int _viewHeigh;

	Matrix3D _cameraTransform;

	Matrix3D _screenTransform;

	Matrix3D _perspectiveProjection;

	void CalculateTransformMatrix();

public:
	Camera( Vector3D rotation, 
			Vector3D position, 
			unsigned int viewWidth, unsigned int viewHeight);

	const Matrix3D& CameraTransform() const;

	const Matrix3D& ScreenTransform() const;

	const Matrix3D& PerspectiveProjection() const;

	Vector3D& GetRotation();
	void SetRotation(Vector3D);

	Vector3D& GetPosition();
	void SetPosition(Vector3D);



	Camera();
	~Camera(void);
};

