#include "IsilmePCH.h"
#include "Camera.h"

Camera::Camera()
{
	x = 0.0f;
	y = 0.0f;
	width = 800;
	height = 600;
}
Camera::Camera(CameraDefinition* def)
{
	x = 0.0f;
	y = 0.0f;
	width = 800;
	height = 600;
}

Camera::~Camera()
{
}

void	Camera::Update(float elapsedTime)
{
	OnUpdate(elapsedTime);
}

void Camera::Apply()
{
	//mHGE->Gfx_SetTransform(0.0f ,0.0f, -x, -y, 0.0f, 1.0f, 1.0f);
}

void Camera::OnUpdate( float elapsedTime )
{

}

CameraDefinition::CameraDefinition()
{
}

CameraDefinition::~CameraDefinition()
{
}

void	CameraDefinition::Parse(TiXmlElement* def)
{
}

CameraPtr CameraDefinition::Create()
{
	return CameraPtr(new Camera(this));
}