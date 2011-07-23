#include "Isilme.h"
#include "ScriptAPI.h"
#include <LuaBind/luabind/lua_include.hpp>
#include <LuaBind/luabind/luabind.hpp>
#include "Engine.h"
#include "FactoryManager.h"
#include "Quest/Quests.h"
#include "Quest/Quest.h"
#include "Quest/Story.h"

namespace ScriptAPI
{
	StatePtr	GetCurrentState()
	{
		return Game::GetSingleton()->GetStateManager()->GetState();
	}

	void RegisterFunctions(lua_State* state)
	{
		luabind::module(state)
			[
				luabind::def("GetState", &GetCurrentState)
			];
	}

	void RegisterQuestAPI(lua_State* state)
	{
		using namespace story;
		
		luabind::module(state)
			[
				luabind::class_<Story, StoryPtr>("Story")
				.def("StartQuest", &Story::StartQuest)
				.def("GetQuest", &Story::GetQuest)
				.def("Load", &Story::Load)
			];
		luabind::globals(state)["Story"] = Game::GetSingleton()->GetStory();

		luabind::module(state)
			[
				luabind::class_<Quest, QuestPtr>("Quest")
				.def("IsActive", &Quest::IsActive)
				.def("IsFinished", &Quest::IsFinished)
			];
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
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();

		luabind::open(state);

		// Vector2
		luabind::module(state)
			[
				luabind::class_<Vector2>("Vector2")
				.def(luabind::constructor<>())
				.def_readwrite("x", &Vector2::x)
				.def_readwrite("y", &Vector2::y)
			];

		// Entity
		luabind::module(state)
			[
				luabind::class_<Entity, EntityPtr>("Entity")
				.def("GetPosition", &Entity::GetPosition)
				.def("SetPosition", &Entity::SetPosition)
				.def("GetAngle", &Entity::GetAngle)
				.def("SetAngle", &Entity::SetAngle)
				.def("Remove", &Entity::Remove)
				.def("RemoveBody", &Entity::RemoveBody)
				.def("GetName", &Entity::GetName)
				.def("IsRemoved", &Entity::IsRemoved)
			];

		// Behaviour
		luabind::module(state)
			[
				luabind::class_<Behaviour, BehaviourPtr>("Behaviour")
				.def("GetActor", &Behaviour::GetActor)
				.def("StartAction", &Behaviour::StartAction)
				.def("IsActive", &Behaviour::IsActive)
				.def("SetActive", &Behaviour::SetActive)
			];

		// ActionState
		luabind::module(state)
			[
				luabind::class_<action::ActionState>("ActionState")
				.enum_("constants")
				[
					luabind::value("Ready", action::Ready),
					luabind::value("Beginnig", action::Beginning),
					luabind::value("Done", action::Done),
					luabind::value("Doing", action::Doing),
					luabind::value("Ending", action::Ending),
					luabind::value("Failed", action::Failed)
				]
			];

		// Action
		luabind::module(state)
			[
				luabind::class_<Action, ActionPtr>("Action")
				.def("GetActor", &Action::GetActor)
				.def("GetState", &Action::GetState)
				.def("Stop", &Action::Stop)
			];

		// Layer
		luabind::module(state)
			[
				luabind::class_<Layer, LayerPtr>("Layer")
				.def("Add", &Layer::Add)
			];

		// Level
		luabind::module(state)
			[
				luabind::class_<Level, LevelPtr>("Level")
				.def("GetLayer", &Level::GetLayer)
				.def("AddLayer", &Level::AddLayer)
				.def("Clear", &Level::Clear)
				.def("CreateEntity", &Level::CreateEntity)
				.def("Load", &Level::Load)
			];

		// State
		luabind::module(state)
			[
				luabind::class_<State, StatePtr>("State")
				.def("Close", &State::Close)
				.def("GetLevel", &State::GetLevel)
			];

		// Factory
		luabind::module(state)
			[
				luabind::class_<FactoryManager, FactoryPtr>("Factory")
				.def("DestroyEntity", (void(FactoryManager::*)(EntityPtr))&FactoryManager::DestroyEntity)
				.def("DestroyEntity", (void(FactoryManager::*)(std::string))&FactoryManager::DestroyEntity)
				.def("GetEntity", &FactoryManager::GetEntity)
			];
		luabind::globals(state)["Factory"] = FactoryManager::GetSingleton();

		RegisterQuestAPI(state);
		RegisterFunctions(state);
		RegisterGUIAPI(state);
	}
};