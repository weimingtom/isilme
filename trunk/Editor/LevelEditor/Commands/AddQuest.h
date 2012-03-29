#pragma once
#include "../Stdafx.h"

using namespace System;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddQuest : public Common::ICommand
		{
		public:
			AddQuest(StoryProxy^ story, QuestProxy^ quest);

			virtual void Execute() override;

			virtual void Unexecute() override;
		private:
			StoryProxy^ mStory;
			QuestProxy^ mQuest;
		};
	}
}