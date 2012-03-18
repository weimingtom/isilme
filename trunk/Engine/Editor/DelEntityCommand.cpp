#include "IsilmePCH.h"
#include "DelEntityCommand.h"
#include "Core/Layer.h"
#include "Core/Entity.h"

namespace editor
{
	DelEntityCommand::DelEntityCommand(LayerPtr layer, EntityPtr entity)
	{
		mLayer = layer;
		mEntity = entity;
	}

	DelEntityCommand::~DelEntityCommand()
	{
	}

	void	DelEntityCommand::Execute()
	{
		mLayer->Remove(mEntity);
	}

	void	DelEntityCommand::Unexecute()
	{
		mLayer->Add(mEntity);
	}
};