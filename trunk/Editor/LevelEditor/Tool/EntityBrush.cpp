#include "Stdafx.h"
#include "EntityBrush.h"
#include "..\Commands\AddEntity.h"
#include "..\Proxy\EntityProxy.h"
#include "../Proxy/FolderProxy.h"
#include "../Proxy/LayerProxy.h"
#include "..\View\EntityPaletteTool.h"

 using namespace Runtime::InteropServices;

namespace LevelEditor
{
	namespace Tool
	{
		EntityBrush::EntityBrush(Common::CommandManager^ commandManager)
		{
			mCommandManager = commandManager;
			mUseGrid = false;
		}

		EntityBrush::~EntityBrush()
		{

		}

		void EntityBrush::OnMouseUp( MouseData^ mouse )
		{
			if (mouse->button != MouseKey::LeftButton)
				return;

			Vector2 position(mouse->x, mouse->y);

			position.x /= 64;
			position.y /= 64;

			LayerProxy^ layer = Layer;
			SharedCLIPtr<::Layer>* lp = layer->mLayer;
			LayerPtr nativeLayer = lp->Value;
			LevelPtr nativeLevel = nativeLayer->GetLevel();

			position.x += layer->mLayer->Value->GetLevel()->GetActiveCamera()->x;
			position.y += layer->mLayer->Value->GetLevel()->GetActiveCamera()->y;

			if (UseGrid)
			{
				int n = position.x / Layer->Grid->Step;
				float x = n * Layer->Grid->Step;

				n = position.y / Layer->Grid->Step;
				float y = n * Layer->Grid->Step;

				position.Set(x,y);
			}

			PaletteItemProxy^ paletteItem = LevelEditor::View::EntityPaletteTool::Instance->SelectedItem;
			if (paletteItem == nullptr)
				return;

			EntityType = paletteItem->FullName;

			EntityProxy^ entity = gcnew EntityProxy(FactoryManager::GetSingleton()->CreateEntity(mEntityType, ""));
			entity->mEntity->Value->SetPosition(position);

			Commands::AddEntity^ command = gcnew Commands::AddEntity(layer, entity);

		//	SelectedObject = gcnew Proxy::EntityProxy(entity);
			//command->Execute();
			mCommandManager->Execute(command);
		}

		void EntityBrush::OnMouseDown( MouseData^ mouse )
		{
			if (mouse->button != MouseKey::LeftButton)
				return;
		}

		void EntityBrush::OnMouseMove( MouseData^ mouse )
		{

		}

		void EntityBrush::EntityType::set(String^ value)
		{
			IntPtr p = Marshal::StringToHGlobalAnsi(value);
			mEntityType = static_cast<char*>(p.ToPointer());
		}

		bool EntityBrush::UseGrid::get()
		{
			return mUseGrid;
		}

		void EntityBrush::UseGrid::set(bool value)
		{
			mUseGrid = value;
		}
	}
}