#include "Stdafx.h"
#include "RemoveQuest.h"
#include "..\Proxy\StoryProxy.h"
#include "..\Proxy\QuestProxy.h"

namespace LevelEditor
{
	namespace Commands
	{
		RemoveQuest::RemoveQuest( Proxy::StoryProxy^ story, Proxy::QuestProxy^ quest )
		{
			mStory = story;
			mQuest = quest;
		}

		void RemoveQuest::Execute()
		{
			mStory->RemoveQuest(mQuest);
		}

		void RemoveQuest::Unexecute()
		{
			mStory->AddQuest(mQuest);
		}

	}
}