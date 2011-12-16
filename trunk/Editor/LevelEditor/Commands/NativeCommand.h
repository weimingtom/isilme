#pragma once
#include "Engine/Editor/Command.h"

namespace LevelEditor
{
	namespace Commands
	{
		public ref class NativeCommand : public Common::ICommand
		{
		public:
			NativeCommand(editor::Command* body);

			virtual void Execute();

			virtual void Unexecute();
		private:
			editor::Command* mBody;
		};
	}
}