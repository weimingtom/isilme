#include "ZombieLand.h"
#include "Cameras.h"

namespace camera
{
	CameraPtr FollowingCameraDef::Create()
	{
		return CameraPtr(new FollowingCamera(this));
	}

	void FollowingCameraDef::Parse(TiXmlElement* element)
	{
		CameraDefinition::Parse(element);

		entityName = "Player";
	}

	FollowingCamera::FollowingCamera(FollowingCameraDef* def) : Camera(def)
	{
		mName = def->entityName;
		x = 0.0f;
		y = 0.0f;
		width = 13.0f;
		height = 9.0f;
		angle = 0.0f;
	}

	FollowingCamera::~FollowingCamera()
	{
	}

	void FollowingCamera::SetPlayer(EntityPtr player)
	{
		mPlayer = player;
		Update(0.0f);
	}

	void FollowingCamera::Update(float elapsedTime)
	{
		if (mPlayer.lock() == 0)
		{
			mPlayer = FactoryManager::GetSingleton()->GetEntity(mName);
		}

		x = floor(mPlayer.lock()->GetPosition().x * 64) / 64.0f - 6.5f;
		y = floor(mPlayer.lock()->GetPosition().y * 64) / 64.0f - 4.0f;

		/*if (mPlayer->GetPosition().x < x + 1.0f)
			x = mPlayer->GetPosition().x - 1.0f;

		if (mPlayer->GetPosition().y < y + 1.0f)
			y = mPlayer->GetPosition().y - 1.0f;

		if (mPlayer->GetPosition().x > x + width - 1.0f)
			x = mPlayer->GetPosition().x - width + 1.0f;

		if (mPlayer->GetPosition().y > y + height - 1.0f)
			y = mPlayer->GetPosition().y - height + 1.0f;*/
	}
};