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

		
		/// �������� �������
		void			Update(float elapsedTime);

		/// ��������� �������
		void			Load(std::string fileName);

		/// ���������� ����� �� �����
		QuestPtr		GetQuest(std::string name);

		/// �������� ���������� ������
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