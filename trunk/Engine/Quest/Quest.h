#ifndef ISILME_STORY_QUEST_H
#define ISILME_STORY_QUEST_H

#include "Quests.h"
#include <string>

namespace story
{
	class IsilmeExport Quest
	{
		friend class Story;
	public:
		static QuestPtr Load(TiXmlElement* element);
		Quest();
		virtual ~Quest();

		/// Возвращает имя квеста
		std::string		GetName();
		void			SetName(std::string name);

		/// Возвращает заголовок квеста
		std::string		GetTitle();
		void			SetTitle(std::string title);

		/// Возвращает стадию квеста
		int				GetStage();
		void			SetStage(int stage);

		std::string		GetText();

		std::string		GetDescription();
		void			SetDescription(std::string description);

		void			OnUpdate(float elapsedTime);

		bool			IsActive();

		bool			IsFinished();

		/// Выполняется в начале квеста
		void			OnStart();
		void			OnFinished();

		void			SetStartScript(std::string script);

		void			SetFinishScript(std::string scritpt);

	protected:
		StoryWPtr	mStory;
		std::string mName;
		std::string mTitle;
		std::string mDescription;
		std::string mText;
		bool	isActive;
		bool	isFinished;

		luabind::object		mStartScript;
		luabind::object		mFinishScript;
		StageMap		mStages;
		StagePtr		mCurrentStage;
	};
};

#endif