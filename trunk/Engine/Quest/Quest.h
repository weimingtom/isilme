#ifndef ISILME_STORY_QUEST_H
#define ISILME_STORY_QUEST_H

#include "Quests.h"
#include <string>

namespace story
{
	class IsilmeExport Quest : public boost::enable_shared_from_this<Quest>
	{
		friend class Story;
	public:
		static QuestPtr Load(TiXmlElement* element);
		Quest();
		virtual ~Quest();

		/// ���������� ��� ������
		std::string		GetName();
		void			SetName(std::string name);

		/// ���������� ��������� ������
		std::string		GetTitle();
		void			SetTitle(std::string title);

		/// ���������� ������ ������
		StagePtr		GetStage();
		void			SetStage(int stage);

		std::string		GetText();

		std::string		GetDescription();
		void			SetDescription(std::string description);

		void			OnUpdate(float elapsedTime);

		bool			IsActive();

		bool			IsFinished();

		/// ����������� � ������ ������
		void			OnStart();
		void			OnFinished();

		void			SetStartScript(std::string script);

		void			SetFinishScript(std::string scritpt);

		void			AddSolution(SolutionPtr	solution);
	protected:
		StoryWPtr	mStory;
		std::string mName;
		std::string mTitle;
		std::string mDescription;
		std::string mText;
		bool	isActive;
		bool	isFinished;
		SolutionList	mSolutions;

		luabind::object		mStartScript;
		luabind::object		mFinishScript;
		StageMap		mStages;
		StagePtr		mCurrentStage;
	};
};

#endif