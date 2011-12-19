#include "Stdafx.h"
#include "SelectorTool.h"
#include "../Proxy/EntityProxy.h"
#include "../Proxy/LayerProxy.h"
#include "../Proxy/LevelProxy.h"
#include "../View/LevelEditorWindow.h"

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
				float dx = Layer->Level->mLevel->Value->GetActiveCamera()->x;
				float dy = Layer->Level->mLevel->Value->GetActiveCamera()->y;

				EntityProxy^ e = dynamic_cast<EntityProxy^>(View::LevelEditorWindow::Instance->SelectedObject);
				e->mEntity->Value->SetPosition(mouse->x / 64.0f + dx, mouse->y / 64.0f + dy);
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
				isMoving = true;
		}

		void SelectorTool::OnMouseMove( MouseData^ mouse )
		{
			if (isMoving)
			{
				float dx = Layer->Level->mLevel->Value->GetActiveCamera()->x;
				float dy = Layer->Level->mLevel->Value->GetActiveCamera()->y;

				EntityProxy^ e = dynamic_cast<EntityProxy^>(View::LevelEditorWindow::Instance->SelectedObject);
				e->mEntity->Value->SetPosition(mouse->x / 64.0f + dx, mouse->y / 64.0f + dy);
			}

		}

		EntityProxy^ SelectorTool::GetEntity( MouseData^ mouse )
		{
			
			if (Layer != nullptr)
			{
				EntityProxy^ e;
				float dx = Layer->Level->mLevel->Value->GetActiveCamera()->x;
				float dy = Layer->Level->mLevel->Value->GetActiveCamera()->y;
				for each (EntityProxy^ entity in Layer->Entities)
				{
					if (abs(entity->Position->X - mouse->x / 64.0f - dx) < 1 && abs(entity->Position->Y - mouse->y / 64.0f - dy) < 1)
						return entity;
				}
			}
			return nullptr;
		}

	}
}