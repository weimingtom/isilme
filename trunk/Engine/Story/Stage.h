#ifndef ISILME_STORY_STAGE_H
#define ISILME_STORY_STAGE_H

#include "Quests.h"
#include "../Core/Script.h"

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
		std::string GetText() const;

		void	SetText(std::string text);

		/// Завершает ли стадия квест
		bool	IsFinishQuest();

		void	OnStart();
		void	OnUpdate(float elapsedTime);

		QuestPtr	GetQuest();

		// Gets script for OnStart event
		ScriptPtr	GetStartScript();

		/// Gets script for OnUpdate event
		ScriptPtr	GetUpdateScript();

		void SetID( int value );
	private:
		int mID;
		std::string mText;
		::Script mStartScript;
		::Script mUpdateScript;
		QuestWPtr	mQuest;
		bool	isFinish;
	};
};
#endif