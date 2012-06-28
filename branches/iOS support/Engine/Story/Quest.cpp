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
#include "Story.h"
#include "Quest.h"
#include "Stage.h"
#include "Engine/ScriptAPI.h"

namespace story
{
	QuestPtr Quest::Load(TiXmlElement* element)
	{
		lua_State* state = Engine::GetSingleton()->GetLua();
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

		if (element->Attribute("StartScript"))
		{
			const char* attr = element->Attribute("StartScript");
			q->mStartScript.Set(attr ? attr : "", "quest");
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

		if (mStartScript.IsValid())
			mStartScript.GetLuaObject()(me);
	}

	void	Quest::OnFinished()
	{
		isFinished = true;
		isActive = false;
		if (mFinishScript.IsValid() != 0)
			mFinishScript.GetLuaObject()(mFinishScript);
	}

	bool	Quest::IsActive()
	{
		return isActive;
	}

	bool	Quest::IsFinished()
	{
		return isFinished;
	}

	int Quest::GetStageCount() const
	{
		return mStages.size();
	}

	story::StagePtr Quest::GetStageAtIndex( int index ) const
	{
		StageMap::const_iterator it = mStages.begin();
		for (int i = 0; i < index; ++i)
		{
			it++;
		}
		return it->second;
	}

	void Quest::AddStage( StagePtr stage )
	{
		mStages[stage->GetID()] = stage;
	}

	void Quest::RemoveStage( StagePtr stage )
	{
		StageMap::iterator it = mStages.find(stage->GetID());
		if (it != mStages.end())
			mStages.erase(it);
	}

	ScriptPtr Quest::GetStartScript()
	{
		return &mStartScript;
	}

	ScriptPtr Quest::GetFinishScript()
	{
		return &mFinishScript;
	}

};