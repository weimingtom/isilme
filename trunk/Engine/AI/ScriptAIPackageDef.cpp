#include "IsilmePCH.h"
#include "ScriptAIPackageDef.h"
#include <luabind/adopt_policy.hpp>
#include "Core/Wrappers/AIPackageWrapper.h"


ScriptAIPackageDef::ScriptAIPackageDef()
{

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
	//AIPackagePtr result = luabind::call_function<AIPackagePtr>(state, mClassName.c_str());
	
	//AIPackagePtr wrapper(new AIPackageWrapper());

	std::string test =  "return function end;";
	luaL_dostring(state, "local o = KeepHealthPackage();o:CheckCondition();");
	luaL_dostring(state, "o:CheckCondition()");
	AIPackagePtr result = luabind::call_function<AIPackagePtr>(state, mClassName.c_str());
//	luabind::object wrapped = luabind::object(state, result);

	return result; // /*AIPackagePtr(result); //*/AIPackagePtr(luabind::object_cast<AIPackage*>(wrapped));
}
