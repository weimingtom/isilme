#ifndef ISILME_SCRIPTAPI_H
#define ISILME_SCRIPTAPI_H

#include <string>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>

namespace ScriptAPI
{
	void ISILME_API RegisterEngineAPI();

	luabind::object		ISILME_API MakeFunction(std::string params, std::string body);
};
#endif