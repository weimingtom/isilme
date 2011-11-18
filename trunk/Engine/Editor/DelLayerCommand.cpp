#include "IsilmePCH.h"
#include "DelLayerCommand.h"
#include "Level.h"
#include "Layer.h"

namespace editor
{
	DelLayerCommand::DelLayerCommand(LevelPtr level, LayerPtr layer)
	{
		mLevel = level;
		mLayer = layer;
	}

	DelLayerCommand::~DelLayerCommand()
	{
	}

	void DelLayerCommand::Execute()
	{
		mLevel->RemoveLayer(mLayer);
	}

	void DelLayerCommand::Unexecute()
	{
		mLevel->AddLayer(mLayer);
	}
};