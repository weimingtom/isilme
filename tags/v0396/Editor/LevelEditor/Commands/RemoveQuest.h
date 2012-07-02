#pragma  once
#include "../Stdafx.h"

using namespace System;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class RemoveQuest : public Common::ICommand
		{
		public:
			RemoveQuest(Proxy::StoryProxy^ story, Proxy::QuestProxy^ quest);

			virtual void Execute() override;

			virtual void Unexecute() override;
		private:
			Proxy::StoryProxy^ mStory;
			Proxy::QuestProxy^ mQuest;
		};

	}
}