#include "Stdafx.h"
#include "EntityBrush.h"
#include "..\Commands\AddEntity.h"

 using namespace Runtime::InteropServices;

namespace LevelEditor
{
	namespace Brush
	{
		EntityBrush::EntityBrush(CommandManager^ commandManager)
		{
			mCommandManager = commandManager;
		}

		EntityBrush::~EntityBrush()
		{

		}

		void EntityBrush::OnMouseUp( int x, int y )
		{
			Vector2 position(x, y);

			position.x /= 64;
			position.y /= 64;

			LayerPtr layer = FactoryManager::GetSingleton()->GetLevel("Level2")->GetLayer("Trees");
			EntityPtr entity = FactoryManager::GetSingleton()->CreateEntity("Cars/Car1", "");
			entity->SetPosition(position);

			Commands::AddEntity^ command = gcnew Commands::AddEntity(layer, entity);

		//	SelectedObject = gcnew Proxy::EntityProxy(entity);
			//command->Execute();
			mCommandManager->Execute(command);
		}

		void EntityBrush::OnMouseDown( int x, int y )
		{

		}

		void EntityBrush::OnMouseMove( int x, int y )
		{

		}

		void EntityBrush::EntityType::set(String^ value)
		{
			IntPtr p = Marshal::StringToHGlobalAnsi(value);
			mEntityType = static_cast<char*>(p.ToPointer());
		}

	}
}