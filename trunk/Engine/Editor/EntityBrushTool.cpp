#include "Isilme.h"
#include "EntityBrushTool.h"

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
	}

	void EntityBrushTool::SetEntityTypeID(std::string id)
	{
		mEntityTypeID = id;
	}
};