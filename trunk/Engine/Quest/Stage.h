#ifndef ISILME_STORY_STAGE_H
#define ISILME_STORY_STAGE_H

#include "Quests.h"

namespace story
{
	class IsilmeExport Stage : public boost::enable_shared_from_this<Stage>
	{
		friend class Quest;
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