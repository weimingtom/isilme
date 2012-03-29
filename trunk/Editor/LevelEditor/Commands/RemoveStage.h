#pragma  once
#include "../Stdafx.h"

using namespace System;
using namespace LevelEditor::Proxy;

namespace LevelEditor
{
	namespace Commands
	{
		public ref class RemoveStage : public Common::ICommand
		{
		public:
			RemoveStage(Proxy::QuestProxy^ quest, Proxy::StageProxy^ stage);

			virtual void Execute() override;

			virtual void Unexecute() override;
		private:
			Proxy::QuestProxy^ mQuest;
			Proxy::StageProxy^ mStage;
		};
	}
}