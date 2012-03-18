#include "IsilmePCH.h"
#include "ScriptAIPackageDef.h"
#include <luabind/adopt_policy.hpp>
#include "Wrappers/AIPackageWrapper.h"

static AIPackagePtr mStaticPackage;
static bool isInit = false;

void __setStaticPackage(AIPackagePtr package)
{
	mStaticPackage = package;
}


ScriptAIPackageDef::ScriptAIPackageDef()
{
	if (!isInit)
	{
		isInit = true;
		luabind::module(Engine::GetSingleton()->GetLua())
			[
				luabind::def("__setStaticPackage", &__setStaticPackage)
			];
	}
}

ScriptAIPackageDef::~ScriptAIPackageDef()
{

}

void ScriptAIPackageDef::Parse( TiXmlElement* element )
{
	if (element->Attribute("Class"))
		mClassName = element->Attribute("Class");
}

AIPackagePtr ScriptAIPackageDef::CreatePackage()
{
	if (mClassName == "")
		return AIPackagePtr();

	lua_State* state = Engine::GetSingleton()->GetLua();
	//luabind::object table = luabind::globals(state)[mClassName];
	
	//luabind::object classTable = luabind::globals(state)[mClassName.c_str()];

	//luabind::object result = classTable();
	//luabind ::object test = luabind::call_function<luabind::object>(state, "TestAction");
	char buf[512];
	//sprintf(buf, "function __hack__lua__function__%s()\nreturn %s();\nend;", mClassName.c_str(), mClassName.c_str());
	//luaL_dostring(state, buf);
	AIPackagePtr obj = luabind::call_function<AIPackagePtr>(state, mClassName.c_str());

	AIPackagePtr result(obj);
	
	//AIPackagePtr wrapper(new AIPackageWrapper());

	std::string test =  "return function end;";

	//AIPackagePtr result = mStaticPackage;


	//AIPackagePtr result = luabind::call_function<AIPackagePtr>(state, mClassName.c_str());
//	luabind::object wrapped = luabind::object(state, result);

	return result; // /*AIPackagePtr(result); //*/AIPackagePtr(luabind::object_cast<AIPackage*>(wrapped));
}
