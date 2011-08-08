#include "Isilme.h"
#include "Story.h"
#include "Quest.h"
#include "Solution.h"

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
		TiXmlDocument* document = new TiXmlDocument();

		document->LoadFile(fileName.data());

		TiXmlElement* root = document->RootElement();
		TiXmlElement* questElement = root->FirstChildElement("Quest");

		while (questElement)
		{
			QuestPtr quest = Quest::Load(questElement);
			quest->mStory = shared_from_this();

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
};