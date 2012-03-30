#include "IsilmePCH.h"
#include "Script.h"
#include "ScriptAPI.h"

Script::Script( std::string source, std::string params /*= ""*/ )
{
	mLuaScript = ScriptAPI::MakeFunction(params, source);
}

Script::Script()
{

}

void Script::Set( std::string source, std::string params /*= ""*/ )
{

}

bool Script::IsValid() const
{
	return mLuaScript.is_valid();
}

std::string Script::GetSource() const
{
	return mSource;
}

luabind::object Script::GetLuaObject() const
{
	return mLuaScript;
}

std::string Script::GetParamsString() const
{
	StringList::const_iterator it = mParams.begin();
	std::string result = *it;
	++it;
	while (it != mParams.end())
	{
		result += ", ";
		result += *it;
		++it;
	}

	return result;
}

