//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#include "IsilmePCH.h"
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
