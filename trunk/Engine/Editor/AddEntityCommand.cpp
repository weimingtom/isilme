#include "Isilme.h"
#include "AddEntityCommand.h"
#include "Layer.h"
#include "Entity.h"

namespace editor
{
	AddEntityCommand::AddEntityCommand(LayerPtr layer, EntityPtr entity)
	{
		mLayer = layer;
		mEntity = entity;
	}

	AddEntityCommand::~AddEntityCommand()
	{
	}

	void AddEntityCommand::Execute()
	{	
		mLayer->Add(mEntity);
	}

	void AddEntityCommand::Unexecute()
	{
		mLayer->Remove(mEntity);
	}
};