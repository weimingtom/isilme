#include "Isilme.h"
#include "Stage.h"
#include <tinyxml.h>

namespace story
{
	Stage::Stage()
	{
	}

	Stage::~Stage()
	{
	}

	void		Stage::OnUpdate(float elapsedTime)
	{
	}

	bool		Stage::IsFinishQuest()
	{
		return isFinish;
	}

	StagePtr	Stage::Load(TiXmlElement* element)
	{
		Stage* stage = new Stage();

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
		// Скрипт старта

		return StagePtr(stage);
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