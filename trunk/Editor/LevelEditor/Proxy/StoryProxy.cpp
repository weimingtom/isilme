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

			for (int i = 0; i < story->GetQuestsCount(); ++i)
			{
				story::QuestPtr q = story->GetQuestAtIndex(i);
				QuestProxy^ quest = gcnew QuestProxy(q);
				quest->mStory = this;
				mQuests->Add(quest);
			}
		}

		StoryProxy::~StoryProxy()
		{
			delete mStory;
		}

		void StoryProxy::AddQuest( QuestProxy^ quest )
		{
			mQuests->Add(quest);
			mStory->Value->AddQuest(quest->mQuest->Value);
			quest->mStory = this;
		}

		void StoryProxy::RemoveQuest( QuestProxy^ quest )
		{
			mQuests->Remove(quest);
			mStory->Value->RemoveQuest(quest->mQuest->Value);
			quest->mStory = nullptr;
		}

		System::String^ StoryProxy::GenerateID()
		{
			int n = 1;
			String^ prefix = "Quest";
			bool found;
			do 
			{
				found = true;
				for each(QuestProxy^ quest in Quests)
					if (quest->ID == prefix + n)
					{
						found = false;
						++n;
						break;
					}
			} 
			while (!found);
			return prefix + n;
		}

		ObservableCollection<QuestProxy^>^ StoryProxy::Quests::get()
		{
			return mQuests;
		}
	}
}