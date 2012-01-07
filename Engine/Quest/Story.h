#ifndef ISILME_QUESTS_STORY_H
#define ISILME_QUESTS_STORY_H

#include "Definitions.h"
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
		
		/// �������� �������
		void			Update(float elapsedTime);

		/// ���������� ����� �� �����
		QuestPtr		GetQuest(std::string name);

		QuestList*		GetActiveQuests();

		QuestList*		GetFinishedQuests();

		boost::signal<void(QuestPtr, int)>	OnSetStage;
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