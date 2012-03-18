#ifndef QUESTS_H
#define QUESTS_H

#include "../Definitions.h"

namespace story
{
	class ISpeaker;
	typedef boost::shared_ptr<ISpeaker>		SpeakerPtr;
	typedef boost::weak_ptr<ISpeaker> SpeakerWPtr;

	class Quest;
	typedef boost::shared_ptr<Quest>		QuestPtr;
	typedef	boost::weak_ptr<Quest>			QuestWPtr;
	typedef std::map<std::string, QuestPtr>	QuestMap;
	typedef std::set<QuestPtr>				QuestSet;
	typedef std::list<QuestPtr>				QuestList;

	class Stage;
	typedef boost::shared_ptr<Stage>		StagePtr;
	typedef boost::weak_ptr<Stage>			StageWPtr;
	typedef std::map<int, StagePtr>			StageMap;

	class Story;
	typedef boost::shared_ptr<Story> StoryPtr;
	typedef boost::weak_ptr<Story> StoryWPtr;


	class Conversation;
	typedef boost::shared_ptr<Conversation> ConversationPtr;
	typedef boost::weak_ptr<Conversation> ConversationWPtr;

	class Phrase;
	typedef boost::shared_ptr<Phrase> PhrasePtr;
	typedef boost::weak_ptr<Phrase> PhraseWPtr;
};



//
//
//class IsilmeExport Ending : public Object
//{
//public:
//	Ending();
//	virtual ~Ending();
//	std::list<std::string>*	GetNewTasks();
//	std::string				GetID();
//	std::string				GetDescription();
//	static Ending*			Parse(TiXmlElement*	endingElement);
//
//	std::string				GetConditionFunction();
//	std::string				GetFinishFunction();
//private:
//	std::list<std::string>	mNewTasks;
//	std::string				mID;
//	std::string				mDescription;
//
//	// Сценарии
//	std::string				mConditionFunction;
//	std::string				mFinishFunction;
//};
//
//class IsilmeExport Task: public Object
//{
//public:
//	enum TaskStatus
//	{
//		Passive,
//		Active,
//		Finished
//	};
//	Task();
//	virtual ~Task();
//	std::string		GetID();
//	std::string		GetDescription();
//	std::string		GetTitle();
//	TaskStatus		GetStatus();
//	void			Start();
//	void			Update(float elapsedTime);
//	void			Finish(std::string ending);
//	static Task*	Parse(TiXmlElement* taskElement);
//
//	std::string		GetStartFunction();
//	std::string		GetUpdateFunction();
//private:
//	// Свойства
//	std::string		mID;
//	std::string		mTitle;
//	std::string		mDescription;
//	TaskStatus		mStatus;
//
//	// Решения
//	EndingMap		mEndings;
//	Ending*			mEnding;
//
//	// Сценарии
//	std::string		mStartFunction;
//	std::string		mUpdateFunction;
//};
//
//class Quest : public Object
//{
//public:
//	Quest();
//	virtual ~Quest();
//
//	void			Update(float elapsedTime);
//	void			OnStart();
//	void			StartTask(std::string task);
//	void			FinishTask(std::string task, std::string ending);
//	std::string		GetID();
//	std::string		GetDescription();
//	std::string		GetTitle();
//	TaskSet*		GetActiveTasks();
//	TaskSet*		GetFinishedTasks();
//	static Quest*	Parse(TiXmlElement* element);
//
//	std::string		GetStartFunction();
//	std::string		GetFinishFunction();
//private:
//	TaskMap			mTasks;
//	TaskSet			mActiveTasks;
//	TaskSet			mFinishedTask;
//	std::string		mID;
//	std::string		mDescription;
//	std::string		mTitle;
//
//	// Сценарии
//	std::string		mStartFunction;
//	std::string		mFinishFunction;
//};
//
//class IsilmeExport Story : public Object
//{
//public:
//	Story();
//	virtual ~Story();
//
//	/// Обновить историю
//	void			Update(float elapsedTime);
//
//	/// Начать выполнение задания
//	void			StartQuest(std::string quest);
//
//	/// Загрузить историю
//	void			Load(std::string fileName);
//
//	void			CreateJournal();
//	gcn::Window*	GetJournal();
//private:
//	QuestMap		mQuests;
//	QuestSet		mActiveQuests;
//	QuestSet		mFinishedQuests;
//	QuestSet		mQuestsForStart;
//	gcn::Window*	mJournalWindow;
//};
//
//class IsilmeExport QuestListModel : public gcn::ListModel, public Object
//{
//public:
//	QuestListModel();
//	virtual ~QuestListModel();
//protected:
//};
#endif