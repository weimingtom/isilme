#ifndef EDITOR_DELENTITYCOMMAND_H
#define EDITOR_DELENTITYCOMMAND_H

#include "EditorDefinitions.h"
#include "Command.h"

namespace editor
{
	class DelEntityCommand
	{
	public:
		virtual ~DelEntityCommand();
		virtual void Execute();
		virtual void Unexecute();
	protected:
	private:
	};
};

#endif