#include "Stdafx.h"
#include "AddQuest.h"
#include "../Proxy/QuestProxy.h"
#include "../Proxy/StoryProxy.h"

namespace LevelEditor
{
	namespace Commands
	{

		AddQuest::AddQuest( StoryProxy^ story, QuestProxy^ quest )
		{
			mStory = story;
			mQuest = quest;
		}

		void AddQuest::Execute()
		{
			mStory->AddQuest(mQuest);
		}

		void AddQuest::Unexecute()
		{
			mStory->RemoveQuest(mQuest);
		}

	}
}