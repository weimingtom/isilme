#include "Isilme.h"
#include "Story.h"
#include "Quest.h"
#include "Stage.h"

namespace story
{
	QuestPtr Quest::Load(TiXmlElement* element)
	{
		Quest* quest = new Quest();
		QuestPtr q = QuestPtr(quest);
		TiXmlElement* stageElement = element->FirstChildElement("Stage");
		
		q->mTitle = element->Attribute("Title") ? element->Attribute("Title") : "";
		q->mName = element->Attribute("Name") ? element->Attribute("Name") : "";

		while (stageElement)
		{
			StagePtr stage = Stage::Load(stageElement);
			stage->mQuest = q;
			q->mStages[stage->GetID()] = stage;

			stageElement = stageElement->NextSiblingElement("Stage");
		}
		return q;
	}
	Quest::Quest()
	{
		mText = "";
		isActive = false;
		isFinished = false;
	}

	Quest::~Quest()
	{
	}

	void	Quest::SetStage(int id)
	{
		if (mStages.find(id) == mStages.end())
			return;

		mCurrentStage = mStages[id];
		mText += "\n";
		mText += mCurrentStage->GetText();

		if (!isActive && !isFinished)
		{
			OnStart();
		}
	}

	std::string Quest::GetText()
	{
		return mText;
	}

	int	Quest::GetStage()
	{
		if (mCurrentStage != 0)
			return mCurrentStage->GetID();
		else
			return 0;
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
		if (mCurrentStage != 0)
		{
			if (mCurrentStage->IsFinishQuest())
			{
				isFinished = true;
			}
			else
			{
				mCurrentStage->OnUpdate(elapsedTime);
			}
		}
	}

	void	Quest::OnStart()
	{
		QuestPtr me = mStory.lock()->GetQuest(GetName());
		mStory.lock()->OnStartQuest(me);
		isActive = true;
		isFinished = false;

		if (mStartScript.interpreter() != 0)
			luabind::call_function<void>(mStartScript);
	}

	void	Quest::OnFinished()
	{
		isFinished = true;
		isActive = false;
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