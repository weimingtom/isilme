#include "IsilmePCH.h"
#include "EntityBrushTool.h"
#include "AddEntityCommand.h"
#include "CommandManager.h"
#include "Core/Layer.h"
#include "Core/Level.h"
#include "Core/Entity.h"
#include "Core/FactoryManager.h"
#include "Core/Game.h"
#include "Core/StateManager.h"
#include "Core/State.h"

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
		GetCommandManager()->Execute(coomand);

		Vector2 mouse(x,y);
		mouse *= 1.0f / 64.0f;
		CameraPtr camera = Game::GetSingleton()->GetStateManager()->GetState()->GetCamera();
		mouse.x += camera->x;
		mouse.y += camera->y;
		entity->SetPosition(mouse.x, mouse.y);
		entity->SetAngle(0);
	}

	void EntityBrushTool::SetEntityTypeID(std::string id)
	{
		mEntityTypeID = id;
	}
};