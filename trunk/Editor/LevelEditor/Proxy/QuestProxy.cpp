#include "Stdafx.h"
#include "QuestProxy.h"
#include "StageProxy.h"
#include "StoryProxy.h"

namespace LevelEditor
{
	namespace Proxy
	{
	

		QuestProxy::QuestProxy( story::QuestPtr quest )
		{
			mQuest = new SharedCLIPtr<story::Quest>(quest);
			mStages = gcnew ObservableCollection<StageProxy^>();
			//for (int i =0; i < quest->GetStag)
			//{
			//}
		}

		QuestProxy::~QuestProxy()
		{
			delete mQuest;
		}

		void QuestProxy::AddStage( StageProxy^ stage )
		{

		}

		void QuestProxy::RemoveStage( StageProxy^ stage )
		{

		}

		String^ QuestProxy::ID::get()
		{
			return gcnew String(mQuest->Value->GetName().c_str());
		}

		String^ QuestProxy::Title::get()
		{
			return gcnew String(mQuest->Value->GetTitle().c_str());
		}

		void QuestProxy::Title::set(String^ value)
		{
			
		}

		void QuestProxy::ID::set(String^ value)
		{
		
		}

		ObservableCollection<StageProxy^>^ QuestProxy::Stages::get()
		{
			return mStages;
		}

		StoryProxy^ QuestProxy::Story::get()
		{
			return mStory;
		}
	}
}