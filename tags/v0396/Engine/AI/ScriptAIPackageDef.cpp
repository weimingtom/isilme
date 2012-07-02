//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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
