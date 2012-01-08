#ifndef ISILME_CORE_CAMERAWRAPPER_H
#define ISILME_CORE_CAMERAWRAPPER_H

#include "Definitions.h"
#include "Camera.h"

class ISILME_API CameraWrapper : public Camera, public luabind::wrap_base
{
public:
	virtual void OnUpdate(float elapsedTime);
	static void defaultOnUpdate(Camera* camera, float elapsedTime);
};
#endif