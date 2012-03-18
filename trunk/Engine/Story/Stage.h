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
		/// Загружает стадию квеста из XML-файла
		static StagePtr	Load(TiXmlElement* element);
		Stage();
		virtual ~Stage();

		/// Возвращает ID стадии
		int	GetID();

		/// Возвращает текст стадии
		std::string	GetText();

		/// Завершает ли стадия квест
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