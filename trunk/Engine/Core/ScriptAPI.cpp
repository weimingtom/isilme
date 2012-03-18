#include "IsilmePCH.h"
#include "ScriptAPI.h"
#include <LuaBind/luabind/lua_include.hpp>
#include <LuaBind/luabind/luabind.hpp>
#include "Engine.h"
#include "FactoryManager.h"
#include "Story/Quests.h"
#include "Story/Quest.h"
#include "Story/Story.h"
#include "Story/Stage.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item.h"
#include <luabind/operator.hpp>
#include "AI/Fraction.h"
#include "Game.h"
#include "Entity.h"
#include "Level.h"
#include "Layer.h"
#include "Behaviour.h"
#include "State.h"
#include "StateManager.h"
#include "Wrappers/ActionWrapper.h"
#include "Wrappers/StateWrapper.h"
#include "Wrappers/BehaviourWrapper.h"
#include "Wrappers/AIPackageWrapper.h"
#include "Wrappers/CameraWrapper.h"
#include "luabind/adopt_policy.hpp"
#include "AI/AIBehaviour.h"

namespace ScriptAPI
{
	luabind::object MakeFunction(std::string params, std::string body)
	{
		std::string s;
		s = "return function(";
		s.append(params);
		s.append(")\n");
		s.append(body);
		s.append("\nend;");

		lua_State* state = Engine::GetSingleton()->GetLua();
				
		if (luaL_loadstring(state, s.c_str()) == 0)
		{
			luabind::object f = luabind::object(luabind::from_stack(state, lua_gettop(state)));
			return f();
		}
		else
			return luabind::object();
	}

	StatePtr	GetCurrentState()
	{
		return Game::GetSingleton()->GetStateManager()->GetState();
	}

	void RegisterFunctions(lua_State* state)
	{
		//luabind::module(state)
		//	[
		//		luabind::def("GetState", &GetCurrentState)
		//	];
	}

	void RegisterInventoryAPI(lua_State* state)
	{
		// Инвентарь
		luabind::module(state)
		[
			luabind::class_<inventory::Inventory, inventory::InventoryPtr>("Inventory")
			.def("GetItemByTag", &inventory::Inventory::GetItemByTag)
			.def("GetSlot", &inventory::Inventory::GetSlot)
			.def("IsEquiped", &inventory::Inventory::IsEquiped)
			.def("AddItem", (void (inventory::Inventory::*)(inventory::ItemPtr))&inventory::Inventory::AddItem)
		];

		// Предмет
		luabind::module(state)
		[
			luabind::class_<inventory::Item, inventory::ItemPtr>("Item")
			.def("GetTag", &inventory::Item::GetTag)
			.def("GetAmmo", &inventory::Item::GetAmmo)
			.def("GetMaxAmmo", &inventory::Item::GetMaxAmmo)
			.def("IsInfinity", &inventory::Item::IsInfinity)
			.def("SetAmmo", &inventory::Item::SetAmmo)
			.def("SetMaxAmmo", &inventory::Item::SetMaxAmmo)
			.def("SetInfinity", &inventory::Item::SetInfinity)
			.enum_("Slot")
			[
				luabind::value("Weapon", inventory::Item::Weapon),
				luabind::value("Spell", inventory::Item::Spell)
			]
		];
	}
	void RegisterQuestAPI(lua_State* state)
	{
		using namespace story;
		// Story
		luabind::module(state)
		[
			luabind::class_<Story, StoryPtr>("StoryClass")
			.def("GetQuest", &Story::GetQuest)
			.def("Load", &Story::Load)
		];

		// Quest
		luabind::module(state)
			[
				luabind::class_<Quest, QuestPtr>("Quest")
				.def("IsActive", &Quest::IsActive)
				.def("IsFinished", &Quest::IsFinished)
				.def("GetStage", (int (Quest::*)())&Quest::GetStage)
				.def("GetText", &Quest::GetText)
				.def("GetTitle", &Quest::GetTitle)
				.def("SetStage", &Quest::SetStage)
				.def("GetName", &Quest::GetName)
			];

		luabind::globals(state)["Story"] = Game::GetSingleton()->GetStory();
	}
	
	void RegisterGUIAPI(lua_State* state)
	{
		//luabind::module(state)
		//	[
		//		luabind::class_<gcn::Button>("Button")
		//	];
	}

	void RegisterEngineAPI()
	{
		lua_State* state = Engine::GetSingleton()->GetLua();
		luabind::open(state);

		// Vector2
		luabind::module(state)
			[
				luabind::class_<Vector2>("Vector2")
				.def(luabind::constructor<>())
				.def_readwrite("x", &Vector2::x)
				.def_readwrite("y", &Vector2::y)
				.def("IsValid", &Vector2::IsValid)
				.def("Length", &Vector2::Length)
				.def("LengthSquared", &Vector2::LengthSquared)
				.def("Normalize", &Vector2::Normalize)
				//.def(luabind::self + Vector2())
			];

		// Entity
		luabind::module(state)
			[
				luabind::class_<Entity, EntityPtr>("Entity")
				.def("GetPosition", &Entity::GetPosition)
				.def("SetPosition", (void (Entity::*)(float, float))&Entity::SetPosition)
				//.def("SetPosition", (void (Entity::*)(Vector2))&Entity::SetPosition)
				.def("GetAngle", &Entity::GetAngle)
				.def("SetAngle", &Entity::SetAngle)
				.def("Remove", &Entity::Remove)
				.def("RemoveBody", &Entity::RemoveBody)
				.def("GetName", &Entity::GetName)
				.def("IsRemoved", &Entity::IsRemoved)
				.def("GetBehaviour", &Entity::GetBehaviour)
				.def("GetAngleTo", (float (Entity::*)(EntityPtr))&Entity::GetAngleTo)
				.def("GetAngleTo", (float (Entity::*)(Vector2))&Entity::GetAngleTo)
				.def("GetDistanceTo", (float (Entity::*)(EntityPtr))&Entity::GetDistanceTo)
				.def("GetDistanceTo", (float (Entity::*)(Vector2))&Entity::GetDistanceTo)
				.def("GetBody", &Entity::GetBody)
			];

		// Behaviour
		luabind::module(state)
			[
				luabind::class_<Behaviour, BehaviourPtr, BehaviourWrapper>("Behaviour")
				.def("GetActor", &Behaviour::GetActor)
				.def("GetEntity", &Behaviour::GetActor)
				.def("GetLevel", &Behaviour::GetLevel)
				.def("Think", &Behaviour::OnUpdate, &BehaviourWrapper::defaultThink)
				.def("StartAction", &Behaviour::StartAction)
				.def("IsActive", &Behaviour::IsActive)
				.def("SetActive", &Behaviour::SetActive)
				.def("StartAction", &Behaviour::StartAction)
				
			];

		// AIPackage
		luabind::module(state)
			[
				luabind::class_<AIPackage, AIPackagePtr>("AIPackage"),
				luabind::class_<AIPackageWrapper, AIPackage, AIPackagePtr>("AIPackage")
				.def(luabind::constructor<>())
//				.def("CheckCondition", &AIPackage::CheckCondition, &AIPackageWrapper::defaultCheckCondition)
				.def("CreateAction", &AIPackage::CreateAction, &AIPackageWrapper::defaultCreateAction)
//				.def("GetBehaviour", &AIPackage::GetBehaviour)
//				.def("GetEntity", &AIPackage::GetEntity)
			];

		// AIBehaviour
		luabind::module(state)
			[
				luabind::class_<AIBehaviour, Behaviour>("AIBehaviour")
				.def("AddAIPackage", (void (AIBehaviour::*)(AIPackagePtr))&AIBehaviour::AddAIPackage)
			];

		// ActionState
		luabind::module(state)
			[
				luabind::class_<action::ActionState>("ActionState")
				.enum_("constants")
				[
					luabind::value("Ready", action::Ready),
					luabind::value("Done", action::Done),
					luabind::value("Doing", action::Doing)
				]
			];

		// Action
		luabind::module(state)
			[
				luabind::class_<Action, ActionPtr, ActionWrapper>("Action")
				.def(luabind::constructor<>())
				.def("GetActor", &Action::GetActor)
				.def("GetEntity", &Action::GetEntity)
				.def("GetState", &Action::GetState)
				.def("Stop", &Action::Stop)
				.def("OnDone", &Action::OnDone, &ActionWrapper::defaultOnDone)
				.def("OnStart", (void (Action::*)())&Action::OnStart, &ActionWrapper::defaultOnStart)
				.def("OnUpdate", &Action::OnUpdate, &ActionWrapper::defaultOnUpdate)
				.def("SetDuration", &Action::SetDuration)
				.def("GetDuration", &Action::GetDuration)
				.def("OnForceStop", &Action::OnForceStop, &ActionWrapper::defaultOnForceStop)
			];

		// Layer
		luabind::module(state)
			[
				luabind::class_<Layer, LayerPtr>("Layer")
				.def(luabind::constructor<>())
				.def("GetName", &Layer::GetName)
				.def("SetName", &Layer::SetName)
				.def("Size", &Layer::Size)
				.def("GetEntity", &Layer::GetEntity)
				.def("Clear", &Layer::Clear)
				.def("Remove", &Layer::Remove)
				.def("GetLevel", &Layer::GetLevel)
				.def("IsVisible", &Layer::IsVisible)
				.def("SetVisible", &Layer::SetVisible)
				.def("Add", &Layer::Add)
			];

		// Level
		luabind::module(state)
			[
				luabind::class_<Level, LevelPtr>("Level")
			//	.def("GetLayer", &Level::GetLayer)
			//	.def("AddLayer", &Level::AddLayer)
				.def("Clear", &Level::Clear)
				.def("CreateEntity", &Level::CreateEntity)
				.def("AddLayer", (void (Level::*)(LayerPtr))&Level::AddLayer)
				.def("RemoveLayer", &Level::RemoveLayer)
				.def("Clear", &Level::Clear)
				.def("GetLayer", (LayerPtr (Level::*)(int))&Level::GetLayer)
				.def("GetLayersCount", &Level::GetLayersCount)
				.def("GetID", &Level::GetID)
//				.def("Load", &Level::Load)
			];

		// Camera
		luabind::module(state)
			[
				luabind::class_<Camera, CameraPtr, CameraWrapper>("Camera")
				.def(luabind::constructor<>())
				.def("OnUpdate", &Camera::OnUpdate, &CameraWrapper::defaultOnUpdate)
				.def_readwrite("x", &Camera::x)
				.def_readwrite("y", &Camera::y)
			];

		// State
		luabind::module(state)
			[
				luabind::class_<State, StatePtr, StateWrapper>("State")
				.def(luabind::constructor<>())
				.def("Close", &State::Close)
				.def("GetLevel", &State::GetLevel)
				.def("SetLevel", &State::SetLevel)
				.def("SetPaused", &State::SetPaused)
				.def("OnUpdate", &State::OnUpdate, &StateWrapper::defaultOnUpdate)
				.def("OnStart", &State::OnStart, &StateWrapper::defaultOnStart)
				.def("OnResume", &State::OnResume, &StateWrapper::defaultOnResume)
				.def("GetCamera", &State::GetCamera)
				.def("SetCamera", &State::SetCamera)
			];

		// Factory
		luabind::module(state)
			[
				luabind::class_<FactoryManager, FactoryPtr>("Factory")
				.def("DestroyEntity", (void(FactoryManager::*)(EntityPtr))&FactoryManager::DestroyEntity)
				.def("DestroyEntity", (void(FactoryManager::*)(std::string))&FactoryManager::DestroyEntity)
				.def("GetEntity", &FactoryManager::GetEntity)
			];

		// Fraction
		luabind::module(state)
			[
				luabind::class_<Fraction, FractionPtr>("Fraction")
				.def("GetID", &Fraction::GetID)
				.def("GetName", &Fraction::GetName)
			];

		luabind::module(state)
		[
			luabind::class_<Body>("Body")
		];

		luabind::globals(state)["Factory"] = FactoryManager::GetSingleton();
		RegisterInventoryAPI(state);
		RegisterQuestAPI(state);
		RegisterFunctions(state);
		RegisterGUIAPI(state);
	}
};