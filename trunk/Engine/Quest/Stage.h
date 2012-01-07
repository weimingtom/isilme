#ifndef ISILME_STORY_STAGE_H
#define ISILME_STORY_STAGE_H

#include "Quests.h"

namespace story
{
	class ISILME_API Stage
	{
		friend class Quest;
		friend class Story;
	public:
		/// ��������� ������ ������ �� XML-�����
		static StagePtr	Load(TiXmlElement* element);
		Stage();
		virtual ~Stage();

		/// ���������� ID ������
		int	GetID();

		/// ���������� ����� ������
		std::string	GetText();

		/// ��������� �� ������ �����
		bool	IsFinishQuest();

		void	OnStart();
		void	OnUpdate(float elapsedTime);

		QuestPtr	GetQuest();
	private:
		int mID;
		std::string mText;
		luabind::object mStartScript;
		luabind::object mUpdateScript;
		QuestWPtr	mQuest;
		bool	isFinish;
	};
};
#endif