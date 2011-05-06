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

	void RegisterEngineAPI()
	{
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();

		luabind::open(state);

		luabind::module(state)
			[
				luabind::class_<Vector2>("Vector2")
				.def(luabind::constructor<>())
				.def_readwrite("x", &Vector2::x)
				.def_readwrite("y", &Vector2::y)
			];

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

		luabind::module(state)
			[
				luabind::class_<FactoryManager, FactoryPtr>("Factory")
				.def("DestroyEntity", (void(FactoryManager::*)(EntityPtr))&FactoryManager::DestroyEntity)
				.def("DestroyEntity", (void(FactoryManager::*)(std::string))&FactoryManager::DestroyEntity)
				.def("GetEntity", &FactoryManager::GetEntity)
			];
		luabind::globals(state)["Factory"] = FactoryManager::GetSingleton();
		RegisterQuestAPI(state);
	}
};