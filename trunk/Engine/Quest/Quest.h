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
		Quest();
		virtual ~Quest();

		std::string		GetName();
		void			SetName(std::string name);

		std::string		GetTitle();
		void			SetTitle(std::string title);

		std::string		GetDescription();
		void			SetDescription(std::string description);

		void			OnUpdate(float elapsedTime);

		bool			IsActive();

		bool			IsFinished();

		void			OnStart();
		void			OnFinished();

		void			SetStartScript(std::string script);

		void			SetFinishScript(std::string scritpt);

		void			AddSolution(SolutionPtr	solution);
	protected:
		std::string mName;
		std::string mTitle;
		std::string mDescription;
		bool	isActive;
		bool	isFinished;
		SolutionList	mSolutions;

		luabind::object		mStartScript;
		luabind::object		mFinishScript;
	};
};

#endif