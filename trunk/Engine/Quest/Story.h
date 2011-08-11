#ifndef ISILME_QUESTS_STORY_H
#define ISILME_QUESTS_STORY_H

#include "Definitions.h"
#include "Quests.h"

namespace story
{
	class IsilmeExport Story/* : public boost::enable_shared_from_this<Story>*/
	{
		friend class Quest;
	public:
		void Load(std::string filename);
		Story();
		virtual ~Story();
		
		/// Обновить историю
		void			Update(float elapsedTime);

		/// Возвращает квест по имени
		QuestPtr		GetQuest(std::string name);

		QuestList*		GetActiveQuests();

		QuestList*		GetFinishedQuests();

	protected:
		void			OnStartQuest(QuestPtr quest);
	private:
		QuestMap	mQuests;
		QuestList	mActiveQuests;
		QuestList	mFinishedQuests;

		QuestSet	mQuestsToStart;
		QuestSet	mQuestsToFinish;
	};
};

#endif