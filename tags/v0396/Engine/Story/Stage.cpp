//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
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