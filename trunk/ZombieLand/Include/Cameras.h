#ifndef CAMERAS_H
#define CAMERAS_H

#include "Definitions.h"

#include <string>

namespace camera
{
	class FollowingCameraDef : public CameraDefinition
	{
	public:
		std::string entityName;

		virtual CameraPtr Create();
		virtual void Parse(TiXmlElement* element);
	};

	class FollowingCamera : public Camera
	{
	public:
		FollowingCamera();
		FollowingCamera(FollowingCameraDef* def);
		virtual ~FollowingCamera();

		void	SetPlayer(EntityPtr Player);
		virtual void OnUpdate(float elapsedTime);
		void SetName( std::string name );
	protected:
		EntityWPtr mPlayer;
		std::string mName;
	};
};
#endif