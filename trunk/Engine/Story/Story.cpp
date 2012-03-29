#include "IsilmePCH.h"
#include "Story.h"
#include "Quest.h"
#include "Stage.h"
#include "Core/Game.h"

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

		document->LoadFile(fileName.data());

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