#pragma once
#include "../Stdafx.h"
#include "../SharedCLIPtr.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class StoryProxy : public Common::ProxyObject
		{
		public:
			StoryProxy(story::StoryPtr story);
			virtual ~StoryProxy();

			property ObservableCollection<QuestProxy^>^ Quests
			{
				ObservableCollection<QuestProxy^>^ get();
			}

			void AddQuest(QuestProxy^ quest);

			void RemoveQuest(QuestProxy^ quest);

			System::String^	GenerateID();
		internal:
			SharedCLIPtr<story::Story>* mStory;
		private:
			ObservableCollection<QuestProxy^>^ mQuests;
		};
	}
}