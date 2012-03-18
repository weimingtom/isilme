#include "IsilmePCH.h"
#include "CameraWrapper.h"

void CameraWrapper::OnUpdate( float elapsedTime )
{
	luabind::call_member<void, float>(this, "OnUpdate", elapsedTime);
}

void CameraWrapper::defaultOnUpdate( Camera* camera, float elapsedTime )
{
	camera->Camera::OnUpdate(elapsedTime);
}
