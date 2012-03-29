#include "Stdafx.h"
#include "..\Proxy\QuestProxy.h"
#include "..\Proxy\StageProxy.h"
#include "AddStage.h"

namespace LevelEditor
{
	namespace Commands
	{


		AddStage::AddStage( Proxy::QuestProxy^ quest, Proxy::StageProxy^ stage )
		{
			mQuest = quest;
			mStage = stage;
		}

		void AddStage::Execute()
		{
			mQuest->AddStage(mStage);
		}

		void AddStage::Unexecute()
		{
			mQuest->RemoveStage(mStage);
		}

	}
}