#pragma once
#include "../Stdafx.h"

namespace LevelEditor
{
	namespace Commands
	{
		public ref class AddStage : public Common::ICommand
		{
		public:
			AddStage(Proxy::QuestProxy^ quest, Proxy::StageProxy^ stage);

			virtual void Execute() override;

			virtual void Unexecute() override;
		private:
			Proxy::QuestProxy^ mQuest;
			Proxy::StageProxy^ mStage;
		};
	}
}