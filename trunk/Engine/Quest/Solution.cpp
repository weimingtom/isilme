#include "Isilme.h"
#include "Quests.h"
#include "Solution.h"

namespace story
{
	Solution::Solution()
	{
	}

	Solution::~Solution()
	{
	}

	bool	Solution::OnCheckCondition()
	{
		if (mConditionScript.interpreter() != 0)
		{
			bool result = false;
			try
			{
				result = luabind::call_function<bool>(mConditionScript);
				return result;
			}
			catch (...)
			{
				mConditionScript = luabind::object();
			}
		}

		return false;
	}

	void	Solution::OnTriggered()
	{
		if (mTriggeredScript.interpreter() != 0)
			luabind::call_function<void>(mTriggeredScript);
	}

	void	Solution::SetConditionScript(std::string script)
	{
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
		if (luaL_loadstring(state, script.c_str()) == 0)
		{
			int f = lua_gettop(state);
			mConditionScript = luabind::object(luabind::from_stack(state, f));
		}
	}

	void	Solution::SetTriggeredScript(std::string script)
	{
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
		if (luaL_loadstring(state, script.c_str()) == 0)
		{
			int f = lua_gettop(state);
			mTriggeredScript = luabind::object(luabind::from_stack(state, f));
		}
	}
};