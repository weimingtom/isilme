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
#include "Story.h"
#include "Quest.h"
#include "Stage.h"
#include "Core/Game.h"
#include "../Core/Engine.h"
#include "../Core/ResourceManager.h"

namespace story
{

	Story::Story()
	{
	}

	Story::~Story()
	{
	}

	void Story::Update(float elapsedTime)
	{
		//// Останавливаем законченные квесты
		for (QuestSet::iterator it = mQuestsToFinish.begin(); it != mQuestsToFinish.end(); ++it)
		{
			mFinishedQuests.push_back(*it);
			mActiveQuests.remove(*it);
			(*it)->isActive = false;
			(*it)->isFinished = true;
		}
		mQuestsToFinish.clear();

		for (QuestSet::iterator it = mQuestsToStart.begin(); it != mQuestsToStart.end(); ++it)
		{
			mActiveQuests.push_back(*it);
			(*it)->isActive = true;
			(*it)->isFinished = false;
		}
		mQuestsToStart.clear();

		// Обновляем активные квесты
		for (QuestList::iterator it = mActiveQuests.begin(); it != mActiveQuests.end(); ++it)
		{
			QuestPtr quest = *it;
			quest->OnUpdate(elapsedTime);
			if (quest->IsFinished())
			{
				mQuestsToFinish.insert(quest);
				quest->OnFinished();
			}

		}
	}

	void	Story::OnStartQuest(QuestPtr quest)
	{
		mQuestsToStart.insert(quest);
	}

	QuestPtr	Story::GetQuest(std::string name)
	{
		if (mQuests.find(name) != mQuests.end())
			return mQuests[name];
		else
			return QuestPtr();
	}


	void	Story::Load(std::string fileName)
	{
		//QuestPtr q = QuestPtr(new Quest());
		//q->mName = "Level1";
		//q->mStory = Game::GetSingleton()->GetStory();

		//StagePtr s = StagePtr(new Stage());
		//q->mStages[10] = s;
		//s->mQuest = q;
		//mQuests["Level1"] = q;
		TiXmlDocument* document = new TiXmlDocument();

        char* path = Engine::GetSingleton()->GetResourceManager()->ResourcePath(fileName.c_str());
		document->LoadFile(path);

		TiXmlElement* root = document->RootElement();
		TiXmlElement* questElement = root->FirstChildElement("Quest");

		while (questElement)
		{
			QuestPtr quest = Quest::Load(questElement);
			quest->mStory = Game::GetSingleton()->GetStory();

			mQuests[quest->GetName()] = quest;
			

			questElement = questElement->NextSiblingElement("Quest");
		}
		delete document;

	}

	QuestList* Story::GetActiveQuests()
	{
		return &mActiveQuests;
	}

	QuestList* Story::GetFinishedQuests()
	{
		return &mFinishedQuests;
	}

	void Story::AddQuest( QuestPtr quest )
	{
		mQuests[quest->GetName()] = quest;
	}

	void Story::RemoveQuest( QuestPtr quest )
	{
		QuestMap::iterator it = mQuests.find(quest->GetName());
		if (it != mQuests.end())
			mQuests.erase(it);
	}

	int Story::GetQuestsCount() const
	{
		return mQuests.size();
	}

	story::QuestPtr Story::GetQuestAtIndex( const int index ) const
	{
		QuestMap::const_iterator it = mQuests.begin();
		for (int i = 0; i < index; ++i)
		{
			it++;
		}
		return it->second;
	}

};