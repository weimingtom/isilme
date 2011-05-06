#include "Isilme.h"
#include "Quest.h"
#include "Solution.h"

namespace story
{
	Quest::Quest()
	{
	}

	Quest::~Quest()
	{
	}

	std::string Quest::GetName()
	{
		return mName;
	}

	void	Quest::SetName(std::string name)
	{
		mName = name;
	}

	std::string Quest::GetDescription()
	{
		return mDescription;
	}

	void	Quest::SetDescription(std::string description)
	{
		mDescription = description;
	}

	std::string Quest::GetTitle()
	{
		return mTitle;
	}

	void	Quest::SetTitle(std::string title)
	{
		mTitle = title;
	}

	void	Quest::OnUpdate(float elapsedTime)
	{
		for (SolutionList::iterator it = mSolutions.begin(); it != mSolutions.end(); ++it)
		{
			SolutionPtr solution = *it;
			if (solution->OnCheckCondition())
			{
				isFinished = true;
				solution->OnTriggered();
			}
		}
	}

	void	Quest::OnStart()
	{
		if (mStartScript.interpreter() != 0)
			luabind::call_function<void>(mStartScript);
	}

	void	Quest::OnFinished()
	{
		if (mFinishScript.interpreter() != 0)
			luabind::call_function<void>(mFinishScript);
	}

	bool	Quest::IsActive()
	{
		return isActive;
	}

	bool	Quest::IsFinished()
	{
		return isFinished;
	}

	void	Quest::AddSolution(SolutionPtr solution)
	{
		mSolutions.push_back(solution);
	}

	void	Quest::SetStartScript(std::string script)
	{
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
		if (luaL_loadstring(state, script.c_str()) == 0)
		{
			int f = lua_gettop(state);
			mStartScript = luabind::object(luabind::from_stack(state, f));
		}
	}

	void	Quest::SetFinishScript(std::string script)
	{
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
		if (luaL_loadstring(state, script.c_str()) == 0)
		{
			int f = lua_gettop(state);
			mFinishScript = luabind::object(luabind::from_stack(state, f));
		}
	}
};