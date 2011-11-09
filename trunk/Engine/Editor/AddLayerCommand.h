#ifndef EDITOR_ADDLAYERCOMMAND_H
#define EDITOR_ADDLAYERCOMMAND_H

#include "EditorDefinitions.h"
#include "Command.h"

namespace editor
{
	class AddLayerCommand : public Command
	{
	public:
		AddLayerCommand(LevelPtr level, LayerPtr layer);
		virtual ~AddLayerCommand();

		virtual void Execute();
		virtual void Unexecute();
	private:
		LayerPtr mLayer;
		LevelPtr mLevel;
	};
};

#endif