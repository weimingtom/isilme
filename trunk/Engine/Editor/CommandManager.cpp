#include "IsilmePCH.h"
#include "EditorDefinitions.h"
#include "CommandManager.h"
#include "Command.h"

namespace editor
{
	CommandManager::CommandManager()
	{
	}

	CommandManager::~CommandManager()
	{
	}

	void CommandManager::Execute(CommandPtr command)
	{
		command->Execute();
		mCommands.push(command);

		while (!mUndoneCommands.empty())
			mUndoneCommands.pop();
	}

	bool CommandManager::IsRedoPossible()
	{
		return !mUndoneCommands.empty();
	}

	bool CommandManager::IsUndoPossible()
	{
		return !mCommands.empty();
	}

	void CommandManager::Undo()
	{
		CommandPtr command = mCommands.top();
		command->Unexecute();
		mUndoneCommands.push(command);
		mCommands.pop();
	}

	void CommandManager::Redo()
	{
		CommandPtr command = mUndoneCommands.top();
		command->Execute();
		mCommands.push(command);
		mUndoneCommands.pop();
	}
};