#include "Stdafx.h"
#include "MoveEntity.h"
#include "../Proxy/EntityProxy.h"

namespace LevelEditor
{
	namespace Commands
	{


		MoveEntity::MoveEntity( EntityProxy^ entity, Point^ position )
		{
			mEntity = entity;
			mOldPosition = entity->Position;
			mNewPosition = position;
		}

		void MoveEntity::Execute()
		{
			mEntity->mEntity->Value->SetPosition(mNewPosition->X, mNewPosition->Y);
		}

		void MoveEntity::Unexecute()
		{
			mEntity->mEntity->Value->SetPosition(mOldPosition->X, mOldPosition->Y);
		}

	}
}