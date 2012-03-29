#ifndef ISILME_QUESTS_STORY_H
#define ISILME_QUESTS_STORY_H

#include "Quests.h"

namespace story
{
	class ISILME_API Story/* : public boost::enable_shared_from_this<Story>*/
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

		boost::signal<void(QuestPtr, int)>	OnSetStage;

		/// Adds quest to the story
		///
		/// @param	quest Quest to add
		void			AddQuest(QuestPtr quest);

		/// Removes quest from the tory
		///
		/// @param	quest Quest to remove
		void			RemoveQuest(QuestPtr quest);

		int				GetQuestsCount() const;

		QuestPtr		GetQuestAtIndex(const int index) const;
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