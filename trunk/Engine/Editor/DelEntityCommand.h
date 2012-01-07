#ifndef EDITOR_DELENTITYCOMMAND_H
#define EDITOR_DELENTITYCOMMAND_H

#include "EditorDefinitions.h"
#include "Command.h"

namespace editor
{
	class ISILME_API DelEntityCommand
	{
	public:
		DelEntityCommand(LayerPtr layer, EntityPtr entity);
		virtual ~DelEntityCommand();
		virtual void Execute();
		virtual void Unexecute();
	protected:
	private:
		EntityPtr mEntity;
		LayerPtr mLayer;
	};
};

#endif