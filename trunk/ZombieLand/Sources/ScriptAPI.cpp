#include "ZombieLand.h"
#include "ZombieLand/Behaviour/Player.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Inventory.h"
#include "ZombieLand/Item.h"
#include "Engine/Quest/Stage.h"
#include "Engine/Quest/Story.h"
#include "Engine/Quest/Quest.h"
#include "Engine/ScriptAPI.h"
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>


void	ScriptAPI::RegisterAPI()
{
	Lua* lua = Engine::GetSingleton()->GetLua();
	lua_State* state = lua->GetState();
//	luabind::open(state);

	//luabind::open(state);	
//	RegisterEngineAPI();

	
	// Класс инветнаря
	luabind::module(state)
		[
			luabind::class_<Inventory, InventoryPtr>("Inventory")
			.def("GetItemByTag", &Inventory::GetItemByTag)
			.def("GetSlot", &Inventory::GetSlot)
			.def("IsEquiped", &Inventory::IsEquiped)
		];
	luabind::module(state)
		[
			luabind::class_<Item, ItemPtr>("Item")
			.enum_("Slot")
			[
				luabind::value("Weapon", Item::Weapon),
				luabind::value("Spell", Item::Spell)
			]
		];
	
	//luabind::module(state)
	//[
	//luabind::class_<ClassC>("ClassC")
	//];
	//luabind::module(state)
	//[
	//luabind::class_<ClassD>("ClassD")
	//];

	// Класс игрока
	luabind::module(state)
	[
		luabind::class_<behaviour::Activator, luabind::bases<Behaviour>, BehaviourPtr>("Behaviour")
	];
	luabind::module(state)
	[
		luabind::class_<behaviour::Destroyable, luabind::bases<behaviour::Activator>, BehaviourPtr>("Destroyable")
	];

	luabind::module(state)
		[
			luabind::class_<behaviour::Creature, luabind::bases<behaviour::Destroyable>, behaviour::CreaturePtr>("Creature")
			.def("GetInventory", &behaviour::Creature::GetInventory)
		];
	luabind::module(state)
		[
			luabind::class_<behaviour::Player, luabind::bases<behaviour::Creature>, behaviour::PlayerPtr>("Player")
			.def("GetActor", &behaviour::Player::GetActor)
		];
	
			// Story

	//lua->RegisterFunction<std::string, std::string, std::string, CreateEntity>("CreateEntity");
//	lua->RegisterFunction<bool, std::string, DestroyEntity>("DestroyEntity");
}

bool	ScriptAPI::GiveHP(std::string name, float hp)
{
	try
	{
		EntityPtr entity = FactoryManager::GetSingleton()->GetEntity(name);
		behaviour::DestroyablePtr b = boost::shared_dynamic_cast<behaviour::Destroyable>(entity->GetBehaviour());

		b->SetHealth(b->GetHealth() + hp);
	}
	catch(...)
	{
		return false;
	}
	return true;
}


bool	ScriptAPI::DestroyEntity(std::string name)
{
	EntityPtr entity = FactoryManager::GetSingleton()->GetEntity(name);
	entity->Remove();
	return true;
}

