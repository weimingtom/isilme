#include "Stdafx.h"
#include "RotateEntity.h"
#include "../Proxy/EntityProxy.h"

namespace LevelEditor
{
	namespace Commands
	{


		RotateEntity::RotateEntity( EntityProxy^ entity, float angle )
		{
			mEntity = entity;
			mOldAnge = entity->Angle;
			mNewAngle = angle;
		}

		void RotateEntity::Execute()
		{
			mEntity->mEntity->Value->SetAngle(mNewAngle);
		}

		void RotateEntity::Unexecute()
		{
			mEntity->mEntity->Value->SetAngle(mOldAnge);
		}

	}
}