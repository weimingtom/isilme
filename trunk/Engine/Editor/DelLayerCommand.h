#ifndef EDITOR_DELLAYERCOMMAND_H
#define EDITOR_DELLAYERCOMMAND_H

#include "EditorDefinitions.h"
#include "Definitions.h"
#include "Command.h"

namespace editor
{
	class DelLayerCommand : public Command
	{
	public:
		DelLayerCommand(LevelPtr level, LayerPtr layer);
		virtual ~DelLayerCommand();

		virtual void Execute();
		virtual void Unexecute();
	private:
		LevelPtr mLevel;
		LayerPtr mLayer;
	};
};

#endif