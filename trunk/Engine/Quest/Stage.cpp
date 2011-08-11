#include "Isilme.h"
#include "Stage.h"
#include <tinyxml.h>

int counter = 0;
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
		counter++;
		if (mUpdateScript.interpreter() != 0)
			luabind::call_function<void>(mUpdateScript);
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

		lua_State* state = Engine::GetSingleton()->GetLua()->GetState();
		std::string script = element->Attribute("UpdateScript") ? element->Attribute("UpdateScript") : "";
		if (script != "")
		{
			if (luaL_loadstring(state, script.c_str()) == 0)
			{
				int f = lua_gettop(state);
				stage->mUpdateScript = luabind::object(luabind::from_stack(state, f));
			}
		}
		// Скрипт старта
		script = element->Attribute("StartScript") ? element->Attribute("StartScript") : "";
		if (script != "")
		{
			if (luaL_loadstring(state, script.c_str()) == 0)
			{
				int f = lua_gettop(state);
				stage->mStartScript = luabind::object(luabind::from_stack(state, f));
			}
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

	void	OnStart()
	{
	}

	void	OnUpdate()
	{
	}
};