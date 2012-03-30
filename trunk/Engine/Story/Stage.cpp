#include "IsilmePCH.h"
#include "Quest.h"
#include "Stage.h"
#include "ScriptAPI.h"
#include "Core/Engine.h"
#include "Definitions.h"

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
		if (mUpdateScript.IsValid())
			mUpdateScript.GetLuaObject()(GetQuest(), elapsedTime);
	}

	bool Stage::IsFinishQuest() const
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
			const char* attr = element->Attribute("UpdateScript");
			stage->mUpdateScript.Set(attr ? attr : "", "quest, elapsedTime");
		}

		// Скрипт старта
		if (element->Attribute("StartScript"))
		{
			const char* attr = element->Attribute("StartScript");
			stage->mStartScript.Set(attr ? attr : "", "quest");
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

	std::string Stage::GetText() const
	{
		return mText;
	}

	void	Stage::OnStart()
	{
		if (mStartScript.IsValid())
			mStartScript.GetLuaObject()(GetQuest());
	}

	void Stage::SetText( std::string text )
	{
		mText = text;
	}

	void Stage::SetID( int value )
	{
		mID = value;
	}

	ScriptPtr Stage::GetStartScript()
	{
		return &mStartScript;
	}

	ScriptPtr Stage::GetUpdateScript()
	{
		return &mUpdateScript;
	}

	void Stage::SetFinishQuest( bool value )
	{
		isFinish = value;
	}
};