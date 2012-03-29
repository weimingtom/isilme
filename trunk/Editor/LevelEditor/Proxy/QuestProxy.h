#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		ref class StageCopyData;

		[Serializable]
		public ref class QuestCopyData
		{
		public:
			String^ ID;
			String^ Title;
			System::Collections::Generic::List<StageCopyData^>^ Stages;
		};

		public ref class QuestProxy : public Common::ProxyObject
		{
		public:
			QuestProxy();
			QuestProxy(story::QuestPtr quest);
			QuestProxy(QuestCopyData^ data);

			virtual ~QuestProxy();

			QuestCopyData^ MakeCopy();

			property String^ ID
			{
				String^ get();
				void set(String^ value);
			}

			property String^ Title
			{
				String^ get();
				void set(String^ value);
			}

			property ObservableCollection<StageProxy^>^ Stages
			{
				ObservableCollection<StageProxy^>^ get();
			}

			property StoryProxy^ Story
			{
				StoryProxy^ get();
			}

			void AddStage(StageProxy^ stage);

			void RemoveStage(StageProxy^ stage);

			int		GenerateID();
		private:
			ObservableCollection<StageProxy^>^ mStages;
		internal:
			StoryProxy^ mStory;
			SharedCLIPtr<story::Quest>* mQuest;
		};
	}
}