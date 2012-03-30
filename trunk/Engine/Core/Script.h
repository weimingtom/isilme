#ifndef ISILME_CORE_SCRIPT_H
#define ISILME_CORE_SCRIPT_H

#include "../Definitions.h"

/// @class Script
///
/// Contains script data and some meta-information about script
/// @detail
/// 
class ISILME_API Script
{
public:
	Script();
	Script(std::string source, std::string params = "");

	/// Sets data from source
	void Set(std::string source, std::string params = "");

	/// Checks if lua-script is valid
	bool IsValid() const;

	/// Gets source of the script
	std::string GetSource() const;

	/// Gets lua object
	luabind::object GetLuaObject() const;

	/// Gets all params as string
	std::string GetParamsString() const;
private:
	typedef std::list<std::string> StringList;

	/// Lua code for 
	std::string mSource;

	/// Parameter of the script
	StringList mParams;

	/// Lua object
	luabind::object mLuaScript;
};

#endif