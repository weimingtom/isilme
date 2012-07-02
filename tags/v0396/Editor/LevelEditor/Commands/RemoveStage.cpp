#include "Stdafx.h"
#include "RemoveStage.h"
#include "..\Proxy\QuestProxy.h"
#include "..\Proxy\StageProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
		RemoveStage::RemoveStage( Proxy::QuestProxy^ quest, Proxy::StageProxy^ stage )
		{
			mQuest = quest;
			mStage = stage;
		}

		void RemoveStage::Execute()
		{
			mQuest->RemoveStage(mStage);
		}

		void RemoveStage::Unexecute()
		{
			mQuest->AddStage(mStage);
		}

	}
}