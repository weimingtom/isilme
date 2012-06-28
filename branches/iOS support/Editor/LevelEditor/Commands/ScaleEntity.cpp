#pragma once
#include "Stdafx.h"
#include "ScaleEntity.h"
#include "../Proxy/EntityProxy.h"

namespace LevelEditor
{
	namespace Commands
	{

		ScaleEntity::ScaleEntity( EntityProxy^ entity, float scale )
		{
			mNewScale = scale;
			mEntity = entity;
			mOldScale = mEntity->Scale;
		}

		void ScaleEntity::Execute()
		{
			mEntity->mEntity->Value->SetScale(mNewScale);
		}

		void ScaleEntity::Unexecute()
		{
			mEntity->mEntity->Value->SetScale(mOldScale);
		}

	}
}