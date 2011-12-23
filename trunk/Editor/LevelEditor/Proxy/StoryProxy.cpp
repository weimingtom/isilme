#include "Stdafx.h"
#include "StoryProxy.h"
#include "QuestProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
	

		StoryProxy::StoryProxy( story::StoryPtr story )
		{
			mStory = new SharedCLIPtr<story::Story>(story);
			mQuests = gcnew ObservableCollection<QuestProxy^>();
		}

		StoryProxy::~StoryProxy()
		{
			delete mStory;
		}

		ObservableCollection<QuestProxy^>^ StoryProxy::Quests::get()
		{
			return mQuests;
		}
	}
}