#include "Stdafx.h"
#include "NativeCommand.h"

namespace LevelEditor
{
	namespace Commands
	{
		NativeCommand::NativeCommand(editor::Command* body) :
			mBody(body)
		{
			
		}

		void NativeCommand::Execute()
		{
			mBody->Execute();
		}

		void NativeCommand::Unexecute()
		{
			mBody->Unexecute();
		}
	}
}