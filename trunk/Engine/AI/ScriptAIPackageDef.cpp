#include "IsilmePCH.h"
#include "ScriptAIPackageDef.h"


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

	lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
	//luabind::object table = luabind::globals(state)[mClassName];
	
	//luabind::object classTable = luabind::globals(state)[mClassName.c_str()];

	//luabind::object result = classTable();
	luabind ::object test = luabind::call_function<luabind::object>(state, "TestAction");
	luabind::object result = luabind::call_function<luabind::object>(state, mClassName.c_str());

	return luabind::object_cast<AIPackagePtr>(result);
}
