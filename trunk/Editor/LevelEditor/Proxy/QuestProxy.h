#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class QuestProxy : public Common::ProxyObject
		{
		public:
			QuestProxy(story::QuestPtr quest);
			virtual ~QuestProxy();

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
		private:
			SharedCLIPtr<story::Quest>* mQuest;
			ObservableCollection<StageProxy^>^ mStages;
		internal:
			StoryProxy^ mStory;
		};
	}
}