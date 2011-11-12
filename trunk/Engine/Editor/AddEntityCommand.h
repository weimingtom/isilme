#ifndef EDITOR_ADDENTITYCOMMAND_H
#define EDITOR_ADDENTITYCOMMAND_H

#include "EditorDefinitions.h"
#include "Command.h"

namespace editor
{
	class IsilmeExport AddEntityCommand : public Command
	{
	public:
		AddEntityCommand(LayerPtr layer, EntityPtr entity);
		virtual ~AddEntityCommand();

		virtual void Execute();
		virtual void Unexecute();
	private:
		LayerPtr mLayer;
		EntityPtr mEntity;
	};
};

#endif