#include "Stdafx.h"
#include "QuestProxy.h"
#include "StageProxy.h"
#include "StoryProxy.h"

using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{
	

		QuestProxy::QuestProxy( story::QuestPtr quest )
		{
			mQuest = new SharedCLIPtr<story::Quest>(quest);
			mStages = gcnew ObservableCollection<StageProxy^>();

			for (int i = 0; i < quest->GetStageCount(); ++i)
			{
				StageProxy^ stage = gcnew StageProxy(quest->GetStageAtIndex(i));
				stage->mQuest = this;
				mStages->Add(stage);
			}
		}

		QuestProxy::QuestProxy()
		{
			mQuest = new SharedCLIPtr<story::Quest>(story::QuestPtr(new story::Quest()));
			mStages = gcnew ObservableCollection<StageProxy^>();
		}

		QuestProxy::QuestProxy( QuestCopyData^ data )
		{
			mQuest = new SharedCLIPtr<story::Quest>(story::QuestPtr(new story::Quest()));
			mStages = gcnew ObservableCollection<StageProxy^>();
			ID = data->ID;
			Title = data->Title;

			for each(StageCopyData^ s in data->Stages)
			{
				AddStage(gcnew StageProxy(s));
			}
		}

		QuestProxy::~QuestProxy()
		{
			delete mQuest;
		}

		void QuestProxy::AddStage( StageProxy^ stage )
		{
			mQuest->Value->AddStage(stage->mStage->Value);
			mStages->Add(stage);
			stage->mQuest = this;
		}

		void QuestProxy::RemoveStage( StageProxy^ stage )
		{
			mQuest->Value->RemoveStage(stage->mStage->Value);
			mStages->Remove(stage);
			stage->mQuest = nullptr;
		}

		int QuestProxy::GenerateID()
		{
			int id = mStages->Count * 10 + 10;

			bool found;
			do 
			{
				found = true;
				for each (StageProxy^ stage in Stages)
				{
					if (stage->ID == id)
					{
						found = false;
						id += 10;
						break;
					}
				}
			} 
			while (!found);

			return id;
		}

		QuestCopyData^ QuestProxy::MakeCopy()
		{
			QuestCopyData^ data = gcnew QuestCopyData();
			data->ID = ID;
			data->Title = Title;
			data->Stages = gcnew System::Collections::Generic::List<StageCopyData^>();

			for each(StageProxy^ stage in Stages)
			{
				data->Stages->Add(stage->MakeCopy());
			}

			return data;
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
			mQuest->Value->SetTitle((char*)Marshal::StringToHGlobalAnsi(value).ToPointer());
		}

		void QuestProxy::ID::set(String^ value)
		{
			if (mStory != nullptr)
				mStory->mStory->Value->RemoveQuest(mQuest->Value);
			mQuest->Value->SetName((char*)Marshal::StringToHGlobalAnsi(value).ToPointer());
			if (mStory != nullptr)
				mStory->mStory->Value->AddQuest(mQuest->Value);
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