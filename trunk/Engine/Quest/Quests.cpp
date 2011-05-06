#include "Isilme.h"
#include <TinyXML.h>

//// Endings
//
//Ending::Ending()
//{
//}
//
//Ending::~Ending()
//{
//}
//
//std::string	Ending::GetID()
//{
//	return mID;
//}
//
//std::string	Ending::GetDescription()
//{
//	return mDescription;
//}
//
//std::list<std::string>*	Ending::GetNewTasks()
//{
//	return &mNewTasks;
//}
//
//Ending*		Ending::Parse(TiXmlElement* endingElement)
//{
//	Ending* ending = new Ending();
//
//	const char* attr;
//
//	// Идентификатор
//	attr = endingElement->Attribute("ID");
//	ending->mID = attr ? attr : "Ending";
//
//	// Описание
//	attr = endingElement->Attribute("Description");
//	ending->mDescription = attr ? attr : "";
//
//	// Новые задачи
//	TiXmlElement* newTasksElement = endingElement->FirstChildElement("NewTask");
//	while (newTasksElement)
//	{
//		attr = newTasksElement->Attribute("ID");
//
//		if (attr)
//			ending->mNewTasks.push_back(attr);
//
//		newTasksElement = newTasksElement->NextSiblingElement("NewTask");
//	}
//
//	return ending;
//}
//
//std::string Ending::GetConditionFunction()
//{
//	return mConditionFunction;
//}
//
//std::string Ending::GetFinishFunction()
//{
//	return mFinishFunction;
//}
//
//// Tasks
//
//Task::Task()
//{
//	mStatus = Task::Passive;
//}
//
//Task::~Task()
//{
//}
//
//std::string			Task::GetDescription()
//{
//	return mDescription;
//}
//
//std::string			Task::GetTitle()
//{
//	return mTitle;
//}
//
//std::string			Task::GetID()
//{
//	return mID;
//}
//	
//Task::TaskStatus	Task::GetStatus()
//{
//	return mStatus;
//}
//
//void				Task::Update(float elsapedTime)
//{
//	if (mStatus == Task::Finished)
//	{
//	}
//}
//
//void				Task::Start()
//{
//	mStatus = Task::Active;
//}
//
//void				Task::Finish(std::string ending)
//{
//	mEnding = mEndings[ending];
//	mStatus = Task::Finished;
//}
//
//Task*				Task::Parse(TiXmlElement* taskElement)
//{
//	Task* task = new Task();
//	
//	const char* attr;
//
//	// Идентификатор
//	attr = taskElement->Attribute("ID");
//	task->mID = attr ? attr : "Task";
//
//	// Заголовок
//	attr = taskElement->Attribute("Title");
//	task->mTitle = attr ? attr : "";
//
//	// Описание
//	attr = taskElement->Attribute("Description");
//	task->mDescription = attr ? attr : "";
//
//	// Варианты завершений
//	TiXmlElement* endingElement = taskElement->FirstChildElement("Ending");
//	while (endingElement)
//	{
//		Ending* ending = Ending::Parse(endingElement);
//		task->mEndings[ending->GetID()] = ending;
//		endingElement = endingElement->NextSiblingElement("Ending");
//	}
//
//	return task;
//}
//
//std::string			Task::GetStartFunction()
//{
//	return mStartFunction;
//}
//
//std::string			Task::GetUpdateFunction()
//{
//	return mUpdateFunction;
//}
//
//// Quests
//
//Quest::Quest()
//{
//}
//
//Quest::~Quest()
//{
//}
//
//std::string Quest::GetDescription()
//{
//	return mDescription;
//}
//
//std::string Quest::GetID()
//{
//	return mID;
//}
//
//std::string	Quest::GetTitle()
//{
//	return mTitle;
//}
//
//TaskSet*	Quest::GetActiveTasks()
//{
//	return &mActiveTasks;
//}
//
//TaskSet*	Quest::GetFinishedTasks()
//{
//	return &mFinishedTask;
//}
//
//Quest*		Quest::Parse(TiXmlElement* questElement)
//{
//	Quest* quest = new Quest();
//	
//	const char* attr;
//
//	// Идентификатор
//	attr = questElement->Attribute("ID");
//	quest->mID = attr ? attr : "Quest";
//
//	// Название
//	attr = questElement->Attribute("Title");
//	quest->mTitle = attr ? attr :  "";
//
//	// Описание
//	attr = questElement->Attribute("Description");
//	quest->mDescription = attr ? attr : "";
//
//	// Чтение задач
//	TiXmlElement* taskElement = questElement->FirstChildElement("Task");
//	while (taskElement)
//	{
//		Task*	task = Task::Parse(taskElement);
//		quest->mTasks[task->GetID()] = task;
//		taskElement = taskElement->NextSiblingElement("Task");
//	}
//
//	return quest;
//}
//
//std::string	Quest::GetStartFunction()
//{
//	return mStartFunction;
//}
//
//std::string Quest::GetFinishFunction()
//{
//	return mFinishFunction;
//}
//
//void		Quest::Update(float elapsedTime)
//{
//}
//
//void		Quest::OnStart()
//{
//	// Запускаем скрипт
//	Lua* lua = Engine::GetSingleton()->GetLua();
//	int	r = 0;
//	lua->CallFunction(mStartFunction.c_str(), r);
//
//	// Активируем задачи
//	for (TaskMap::iterator it = mTasks.begin(); it != mTasks.end(); ++it)
//	{
//		mActiveTasks.insert(it->second);
//		it->second->Start();
//	}
//}
//
//// QuestListModel
//QuestListModel::QuestListModel()
//{
//}
//
//QuestListModel::~QuestListModel()
//{
//}
//
