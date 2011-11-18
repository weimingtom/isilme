#include "IsilmePCH.h"
#include "Story.h"
#include "Quest.h"
#include "Stage.h"
#include "Engine/ScriptAPI.h"

namespace story
{
	QuestPtr Quest::Load(TiXmlElement* element)
	{
		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
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

			if (element->Attribute("StartScript"))
			{
				q->mStartScript = ScriptAPI::MakeFunction("quest", element->Attribute("StartScript"));
			}

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

	StagePtr	Quest::GetStage(int stage)
	{
		return mStages[stage];
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

		mStory.lock()->OnSetStage(shared_from_this(), id);
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
		QuestPtr me = shared_from_this();
		mStory.lock()->OnStartQuest(me);
		isActive = true;
		isFinished = false;

		if (mStartScript)
			mStartScript(me);
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
};