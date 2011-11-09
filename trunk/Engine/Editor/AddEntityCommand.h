#ifndef EDITOR_ADDENTITYCOMMAND_H
#define EDITOR_ADDENTITYCOMMAND_H

#include "EditorDefinitions.h"
#include "Command.h"

namespace editor
{
	class AddEntityCommand : public Command
	{
	public:
		AddEntityCommand(LayerPtr layer, EntityPtr entity);
		virtual ~AddEntityCommand();

		virtual void Execute();
		virtual void Unexecute();
	private:
		LayerPtr mLayer;
		EntiryPtr mEntity;
	};
};

#endif