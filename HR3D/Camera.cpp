#include "StdAfx.h"
#include "Camera.h"


Camera::Camera(void)
{
}

Camera::Camera(Vector3D rotation, Vector3D position, 
		unsigned int viewWidth, unsigned int viewHeight)
{
	_rotation = rotation;
	_position = position;
	_viewWidth = viewWidth;
	_viewHeigh = viewHeight;
	
	CalculateTransformMatrix();

	//opengl viewport matrix
	_screenTransform.Set(0,0,(float)(viewWidth / 2));
	_screenTransform.Set(1,1,(float)(viewHeight / 2));
	_screenTransform.Set(3,0,(float)(viewWidth / 2));
	_screenTransform.Set(3,1, (float)(viewHeight / 2));


	//perspectiveProjection = Matrix3D::CreatePerspectiveProjection(1.5f, 1, 1, 1000);
	_perspectiveProjection = Matrix3D::CreatePerspectiveProjection(1.57079632679489661923132169163975144209858469968f,(float)viewWidth / (float)viewHeight, 1, 1000);
}

void Camera::CalculateTransformMatrix()
{
	//create the inverse of the camera transformation
	_cameraTransform = Matrix3D::CreateRotation(-_rotation.GetX(), -_rotation.GetY(), -_rotation.GetZ()) * 
					Matrix3D::CreateTranslation(-_position.GetX(), -_position.GetY(), -_position.GetZ());
}

Vector3D& Camera::GetRotation()
{
	return _rotation;
}

void Camera::SetRotation(Vector3D rotation)
{
	_rotation = rotation;

	//create the inverse of the camera transformation
	CalculateTransformMatrix();
}

Vector3D& Camera::GetPosition()
{
	return _position;
}

void Camera::SetPosition(Vector3D position)
{
	_position = position;

	//create the inverse of the camera transformation
	CalculateTransformMatrix();
}


const Matrix3D& Camera::CameraTransform() const
{
	return _cameraTransform;
}

const Matrix3D& Camera::ScreenTransform() const
{
	return _screenTransform;
}

const Matrix3D& Camera::PerspectiveProjection() const
{
	return _perspectiveProjection;
}

Camera::~Camera(void)
{
}
