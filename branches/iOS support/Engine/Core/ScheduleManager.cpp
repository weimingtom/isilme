//  Copyright (C) 2012 Alexander Alimov, VSTU
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
#include "Scheduler.h"
#include "ScheduleManager.h"


ScheduleManager::ScheduleManager()
{

}

ScheduleManager::~ScheduleManager()
{

}

void ScheduleManager::Update( float elapsedTime )
{
	for (TaskList::iterator it = mTaskList.begin(); it != mTaskList.end(); ++it)
	{
		SchedulerPtr scheduler = *it;
		if (scheduler->IsActive())
			scheduler->OnUpdate(elapsedTime);
	}
}

void ScheduleManager::AddScheduler( SchedulerPtr scheduler, std::string key /*= ""*/ )
{
	mTaskList.push_back(scheduler);
}

SchedulerPtr ScheduleManager::GetScheduler( std::string key ) const
{
	return SchedulerPtr();
}

void ScheduleManager::RemoveScheduler( SchedulerPtr scheduler )
{

}
