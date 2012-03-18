#include "IsilmePCH.h"
#include "ScriptLoader.h"
#include "Core/FactoryManager.h"
#include "Core/MasterFile.h"
#include "Core/Engine.h"
#include "luabind/lua_include.hpp"

namespace serialisation
{


	ScriptLoader::ScriptLoader()
	{

	}

	ScriptLoader::~ScriptLoader()
	{

	}

	EntryPtr ScriptLoader::LoadEntry( std::string filename )
	{
		lua_State* state = Engine::GetSingleton()->GetLua();
		luaL_dofile(state, filename.c_str());

		return EntryPtr();
	}

}