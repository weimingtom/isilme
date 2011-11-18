#include "IsilmePCH.h"
#include "EntityBrushTool.h"
#include "AddEntityCommand.h"

namespace editor
{
	EntityBrushTool::EntityBrushTool()
	{
	}

	EntityBrushTool::~EntityBrushTool()
	{
	}

	void EntityBrushTool::OnMouseMove(LayerPtr layer, float x, float y, int button)
	{
	}

	void EntityBrushTool::OnMouseDown(LayerPtr layer, float x, float y, int button)
	{
	}

	void EntityBrushTool::OnMouseUp(LayerPtr layer, float x, float y, int button)
	{
		EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity(mEntityTypeID, "");
		
		CommandPtr coomand(new AddEntityCommand(layer, entity));
	}

	void EntityBrushTool::SetEntityTypeID(std::string id)
	{
		mEntityTypeID = id;
	}
};