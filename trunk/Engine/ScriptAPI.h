#ifndef ISILME_SCRIPTAPI_H
#define ISILME_SCRIPTAPI_H

#include <string>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>

namespace ScriptAPI
{
	void IsilmeExport RegisterEngineAPI();

	luabind::object		IsilmeExport MakeFunction(std::string params, std::string body);
};
#endif