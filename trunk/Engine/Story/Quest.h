#ifndef ISILME_STORY_QUEST_H
#define ISILME_STORY_QUEST_H

#include "Quests.h"
#include <string>
#include "../Core/Script.h"

namespace story
{
	class ISILME_API Quest : public boost::enable_shared_from_this<Quest>
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
		StagePtr		GetStage(int stage);
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

		int				GetStageCount() const;
		StagePtr		GetStageAtIndex(int index) const;

		void			AddStage(StagePtr stage);

		void			RemoveStage(StagePtr stage);

		/// Gets script for start event
		ScriptPtr		GetStartScript();

		/// Gets script for finish event
		ScriptPtr		GetFinishScript();
	protected:
		StoryWPtr	mStory;
		std::string mName;
		std::string mTitle;
		std::string mDescription;
		std::string mText;
		bool	isActive;
		bool	isFinished;

		Script		mStartScript;
		Script		mFinishScript;
		StageMap		mStages;
		StagePtr		mCurrentStage;
		
	};
};

#endif