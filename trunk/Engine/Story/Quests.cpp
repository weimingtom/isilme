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
//	���� ���� � ����� Isilme SDK.
//
//		Isilme SDK - ��������� ���������: �� ������ ������������������ �� �/���
//		�������� �� �� �������� ������� ����������� ������������ �������� GNU � ��� ����,
//		� ����� ��� ���� ������������ ������ ���������� ������������ �����������;
//		���� ������ 3 ��������, ���� (�� ������ ������) ����� ����� �������
//		������.
//
//		Isilme SDK ���������������� � �������, ��� ��� ����� ��������,
//		�� ���� ������ ��������; ���� ��� ������� �������� ��������� ����
//		��� ����������� ��� ������������ �����. ��������� ��. � ������� �����������
//		������������ �������� GNU.
//
//		�� ������ ���� �������� ����� ������� ����������� ������������ �������� GNU
//		������ � ���� ����������. ���� ��� �� ���, ��.
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
//	// �������������
//	attr = endingElement->Attribute("ID");
//	ending->mID = attr ? attr : "Ending";
//
//	// ��������
//	attr = endingElement->Attribute("Description");
//	ending->mDescription = attr ? attr : "";
//
//	// ����� ������
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
//	// �������������
//	attr = taskElement->Attribute("ID");
//	task->mID = attr ? attr : "Task";
//
//	// ���������
//	attr = taskElement->Attribute("Title");
//	task->mTitle = attr ? attr : "";
//
//	// ��������
//	attr = taskElement->Attribute("Description");
//	task->mDescription = attr ? attr : "";
//
//	// �������� ����������
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
//	// �������������
//	attr = questElement->Attribute("ID");
//	quest->mID = attr ? attr : "Quest";
//
//	// ��������
//	attr = questElement->Attribute("Title");
//	quest->mTitle = attr ? attr :  "";
//
//	// ��������
//	attr = questElement->Attribute("Description");
//	quest->mDescription = attr ? attr : "";
//
//	// ������ �����
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
//	// ��������� ������
//	Lua* lua = Engine::GetSingleton()->GetLua();
//	int	r = 0;
//	lua->CallFunction(mStartFunction.c_str(), r);
//
//	// ���������� ������
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
