#include "Stdafx.h"
#include "EntityBrush.h"
#include "..\Commands\AddEntity.h"
#include "..\Proxy\EntityProxy.h"

 using namespace Runtime::InteropServices;

namespace LevelEditor
{
	namespace Tool
	{
		EntityBrush::EntityBrush(CommandManager^ commandManager)
		{
			mCommandManager = commandManager;
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

			EntityProxy^ entity = gcnew EntityProxy(FactoryManager::GetSingleton()->CreateEntity("Cars/Car1", ""));
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

	}
}