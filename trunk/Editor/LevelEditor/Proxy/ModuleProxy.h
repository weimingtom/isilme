#pragma once
#include "../Stdafx.h"

using namespace System;
using namespace System::Collections::ObjectModel;

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class ModuleProxy
		{
		public:
			ModuleProxy();

			void AddLevel(LevelProxy^ level);
			void RemoveLevel(LevelProxy^ level);
			void AddConversation(ConversationProxy^ conversation);
			void RemoveConversation(ConversationProxy^ conversation);

			property ObservableCollection<LevelProxy^>^ Levels
			{
				ObservableCollection<LevelProxy^>^ get();
			}

			property ObservableCollection<ConversationProxy^>^ Conversations
			{
				ObservableCollection<ConversationProxy^>^ get();
			}

			property StoryProxy^ Story
			{
				StoryProxy^ get();
			}
		private:
			ObservableCollection<LevelProxy^>^ mLevels;
			ObservableCollection<ConversationProxy^>^ mConversations;
			StoryProxy^ mStory;
		};
	}
}
