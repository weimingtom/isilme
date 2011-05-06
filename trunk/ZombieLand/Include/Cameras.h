#ifndef CAMERAS_H
#define CAMERAS_H

#include <Isilme.h>
#include "Definitions.h"

#include <string>

namespace camera
{
	class FollowingCameraDef : public CameraDefinition
	{
	public:
		std::string entityName;

		virtual Camera* Create();
		virtual void Parse(TiXmlElement* element);
	};

	class FollowingCamera : public Camera
	{
	public:
		FollowingCamera(FollowingCameraDef* def);
		virtual ~FollowingCamera();

		void	SetPlayer(EntityPtr Player);
		virtual void Update(float elapsedTime);
	protected:
		EntityWPtr mPlayer;
		std::string mName;
	};
};
#endif