#ifndef ISILME_QUESTS_STORY_H
#define ISILME_QUESTS_STORY_H

#include "Definitions.h"
#include "Quests.h"

namespace story
{
	class IsilmeExport Story
	{
	public:
		Story();
		virtual ~Story();

		
		/// Обновить историю
		void			Update(float elapsedTime);

		/// Загрузить историю
		void			Load(std::string fileName);

		/// Возвращает квест по имени
		QuestPtr		GetQuest(std::string name);

		/// Начинает выполнение квеста
		void			StartQuest(QuestPtr quest);

	private:
		QuestMap	mQuests;
		QuestList	mActiveQuests;
		QuestList	mFinishedQuests;

		QuestSet	mQuestsToStart;
		QuestSet	mQuestsToFinish;
	};
};

#endif