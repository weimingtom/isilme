#include "Stdafx.h"
#include "EntityBrush.h"
#include "..\Commands\AddEntity.h"
#include "..\Proxy\EntityProxy.h"
#include "../Proxy/FolderProxy.h"
#include "../Proxy/LayerProxy.h"
#include "..\View\EntityPaletteTool.h"
#include "..\LevelEditorCommands.h"

 using namespace Runtime::InteropServices;

namespace LevelEditor
{
	namespace Tool
	{
		EntityBrush::EntityBrush(Common::CommandManager^ commandManager)
		{
			mTempEntity = new SharedCLIPtr<Entity>(EntityPtr());
			mCommandManager = commandManager;
		}

		EntityBrush::~EntityBrush()
		{

		}

		void EntityBrush::OnMouseUp( MouseData^ mouse )
		{
			if ((Engine::GetSingleton()->GetInputSystem()->IsKeyUp(HGEK_RBUTTON)) ||(mouse->button == MouseKey::RightButton))
			{
				Angle += 3.14159265f / 4.0f;
				return;
			}

			if (mouse->button != MouseKey::LeftButton)
				return;

			if (!mTempEntity->Value)
				return;

			Proxy::Point^ p = ProcessToLevelCoords(mouse);

			EntityProxy^ entity = gcnew EntityProxy(mTempEntity->Value);
			entity->mEntity->Value->SetPosition(p->X, p->Y);
			entity->mEntity->Value->SetAngle(mDefaultAngle);
			Layer->mLayer->Value->Remove(mTempEntity->Value);
			mTempEntity->Value.reset();

			Commands::AddEntity^ command = gcnew Commands::AddEntity(Layer, entity);

		//	SelectedObject = gcnew Proxy::EntityProxy(entity);
			//command->Execute();
			mCommandManager->Execute(command);
		}

		void EntityBrush::OnMouseDown( MouseData^ mouse )
		{

			if (mouse->button != MouseKey::LeftButton)
				return;
			if (mouse->button == MouseKey::RightButton)
				return;

			PaletteItemProxy^ paletteItem = LevelEditor::View::EntityPaletteTool::Instance->SelectedItem;
			if (paletteItem == nullptr)
				return;

			EntityType = paletteItem->FullName;

			mTempEntity->Value = FactoryManager::GetSingleton()->CreateEntity(mEntityType, "");

			Proxy::Point^ p = ProcessToLevelCoords(mouse);

			mTempEntity->Value->SetPosition(p->X, p->Y);
			mTempEntity->Value->SetAngle(mDefaultAngle);
			Layer->mLayer->Value->Add(mTempEntity->Value);
		}

		void EntityBrush::OnMouseMove( MouseData^ mouse )
		{
			if (!mTempEntity->Value)
				return;

			Proxy::Point^ p = ProcessToLevelCoords(mouse);

			mTempEntity->Value->SetPosition(p->X, p->Y);
			mTempEntity->Value->SetAngle(mDefaultAngle);
		}
		
		void EntityBrush::EntityType::set(String^ value)
		{
			mEntityType = (char*)(Marshal::StringToHGlobalAnsi(value).ToPointer());
		}

		float EntityBrush::Angle::get()
		{
			return mDefaultAngle;
		}

		void EntityBrush::Angle::set(float value)
		{
		
			mDefaultAngle = value;
			if (mDefaultAngle >= 2.0f * 3.14159265f)
				mDefaultAngle = 0;

			if (mTempEntity->Value)
			{
			
				mTempEntity->Value->SetAngle(mDefaultAngle);
			}
		}
	}
}