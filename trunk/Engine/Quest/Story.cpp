#include "Isilme.h"
#include "Story.h"

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

		//// Запускаем стартовавшие квесты
		//for (QuestSet::iterator it = mQuestsForStart.begin(); it != mQuestsForStart.end(); ++it)
		//{
		//	mActiveQuests.insert(*it);
		//}
		//mQuestsForStart.clear();
	}

	void	Story::Load(std::string fileName)
	{
		//TiXmlDocument* document = new TiXmlDocument();

		//document->LoadFile(fileName.data());

		//TiXmlElement* root = document->RootElement();
		//TiXmlElement* questElement = root->FirstChildElement("Quest");

		//while (questElement)
		//{
		//	Quest* quest = Quest::Parse(questElement);
		//	mQuests[quest->GetID()] = quest;
		//	questElement = questElement->NextSiblingElement("Quest");
		//}
		//delete document;
	}
};