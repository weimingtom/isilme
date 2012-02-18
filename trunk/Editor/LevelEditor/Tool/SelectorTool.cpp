#include "Stdafx.h"
#include "SelectorTool.h"
#include "../Proxy/EntityProxy.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/LevelProxy.h"
#include "../View/LevelEditorWindow.h"
#include "../LevelEditorCommands.h"
#include "../Commands/MoveEntity.h"

using namespace System;
using namespace Common;

namespace LevelEditor
{
	namespace Tool
	{


		SelectorTool::SelectorTool( Common::CommandManager^ commandManager )
		{
			mCommandManager = commandManager;
		}

		SelectorTool::~SelectorTool()
		{

		}

		void SelectorTool::OnMouseUp( MouseData^ mouse )
		{
			

			if (isMoving)
			{
				CameraPtr camera = Game::GetSingleton()->GetStateManager()->GetState()->GetCamera();
				float dx = camera->x;
				float dy = camera->y;

				EntityProxy^ e = dynamic_cast<EntityProxy^>(View::LevelEditorWindow::Instance->SelectedObject);
				e->mEntity->Value->SetPosition(mOldX, mOldY);

				Proxy::Point^ p = ProcessToLevelCoords(mouse);

				View::LevelEditorWindow::Instance->CommandManager->Execute(gcnew LevelEditor::Commands::MoveEntity(e, p));
			}
			else
			{
				EntityProxy^ e = GetEntity(mouse);
				View::LevelEditorWindow::Instance->SelectedObject = e;
			}

			isMoving = false;
		}

		void SelectorTool::OnMouseDown( MouseData^ mouse )
		{
			isMoving = false;
			EntityProxy^ e = GetEntity(mouse);
			if (e != nullptr && e == View::LevelEditorWindow::Instance->SelectedObject)
			{
				isMoving = true;
				mOldX = e->Position.X;
				mOldY = e->Position.Y;
			}
		}

		void SelectorTool::OnMouseMove( MouseData^ mouse )
		{
			if (isMoving)
			{
				Proxy::Point^ p = ProcessToLevelCoords(mouse);

				EntityProxy^ e = dynamic_cast<EntityProxy^>(View::LevelEditorWindow::Instance->SelectedObject);
				e->mEntity->Value->SetPosition(p->X, p->Y);
			}

		}

		EntityProxy^ SelectorTool::GetEntity( MouseData^ mouse )
		{

			Proxy::Point^ p = ProcessToLevelCoordsNoGrid(mouse);
			if (Layer != nullptr)
			{
				EntityProxy^ e;

				for each (EntityProxy^ entity in Layer->Entities)
				{
					if (abs(entity->Position.X - p->X) < 1 && abs(entity->Position.Y - p->Y) < 1)
						return entity;
				}
			}
			return nullptr;
		}
	}
}