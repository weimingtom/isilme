//  Copyright (C) 2010-2012 Alexander Alimov, VSTU
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
#ifndef ISILME_CORE_UPDATEMANAGER_H
#define ISILME_CORE_UPDATEMANAGER_H

#include "Definitions.h"

/// @class UpdateManager
class ISILME_API ScheduleManager
{
public:
	ScheduleManager();
	virtual ~ScheduleManager();

	/// Calls OnUpdate method for each scheduler
	/// @param		elapsedTime
	void Update(float elapsedTime);

	/// Adds a scheduler to the task list
	/// @param		scheduler	a scheduler
	/// @param		key			a key assotiated with a scheduler
	void AddScheduler(SchedulerPtr scheduler, std::string key = "");

	/// Gets a scheduler with a given key
	/// @param		key			The key of the schaduler
	SchedulerPtr GetScheduler(std::string key) const;

	/// Remove a scheduler from the task list
	void RemoveScheduler(SchedulerPtr scheduler);
private:
	typedef std::list<SchedulerPtr> TaskList;

	/// All schedulers
	TaskList mTaskList;
};
#endif