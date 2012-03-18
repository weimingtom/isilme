#include "IsilmePCH.h"
#include "Quest.h"
#include "Stage.h"
#include "ScriptAPI.h"
#include "Core/Engine.h"

namespace story
{
	Stage::Stage()
	{
		isFinish = false;
	}

	Stage::~Stage()
	{
	}

	void		Stage::OnUpdate(float elapsedTime)
	{
		if (mUpdateScript)
			mUpdateScript(GetQuest(), elapsedTime);
	}

	bool		Stage::IsFinishQuest()
	{
		return isFinish;
	}

	StagePtr	Stage::Load(TiXmlElement* element)
	{
		StagePtr stage = StagePtr(new Stage());

		stage->mID = 0;
		stage->mText = "";

		// Идентификатор
		element->QueryIntAttribute("ID", &stage->mID);

		// Текст
		if (element->Attribute("Text"))
			stage->mText = element->Attribute("Text");

		// Завершение квеста
		int f = 0;
		element->QueryIntAttribute("FinishQuest", &f);
		stage->isFinish = (f != 0);

		// Скрипт итерации

		lua_State* state = Engine::GetSingleton()->GetLua();

		if (element->Attribute("UpdateScript"))
		{
			stage->mUpdateScript = ScriptAPI::MakeFunction("quest, elapsedTime", element->Attribute("UpdateScript"));
		}

		// Скрипт старта
		if (element->Attribute("StartScript"))
		{
			stage->mStartScript = ScriptAPI::MakeFunction("quest", element->Attribute("StartScript"));
		}

		return stage;
	}

	QuestPtr	Stage::GetQuest()
	{
		return mQuest.lock();
	}

	int	Stage::GetID()
	{
		return mID;
	}

	std::string Stage::GetText()
	{
		return mText;
	}

	void	Stage::OnStart()
	{
		if (mStartScript)
			mStartScript(GetQuest());
	}

};