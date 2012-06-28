//  Copyright (C) 2010-2012 VSTU
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
#include "Behaviour.h"
#include "Action.h"
#include "FactoryManager.h"

BehaviourPtr Behaviour::New()
{
	return BehaviourPtr(new Behaviour(0));
}

Behaviour::Behaviour()
{
	isActive = true;
}

Behaviour::Behaviour(BehaviourDefinition* def)
{
	isActive = true;
}

Behaviour::~Behaviour()
{
}

void		Behaviour::SetActor(EntityPtr actor)
{
	mActor = actor;
}

EntityPtr		Behaviour::GetActor()
{
	return mActor.lock();
}

LevelPtr		Behaviour::GetLevel()
{
	return GetActor()->GetLevel();
}

void		Behaviour::Update(float elapsedTime)
{
	if (!isActive)
	{
		return;
	}

	OnUpdate(elapsedTime);
	UpdateActions(elapsedTime);
}

void		Behaviour::UpdateActions(float elapsedTime)
{
	ActionList::iterator it = mActiveActions.begin(); 
	while (it != mActiveActions.end())
	{
		(*it)->Update(elapsedTime);
		if ((*it)->GetState() == action::Done)
		{
			// ������� ��������
			it = mActiveActions.erase(it);
		}
		else
		{
			// ����������
			//mActionMask |= (*it)->GetMask();
			++it;
		}
	}
}

void		Behaviour::StartAction(ActionPtr action)
{
	mActiveActions.push_back(action);
	action->OnStart(shared_from_this());
}

void		Behaviour::SetActive(bool value)
{
	isActive = value;
}

bool		Behaviour::IsActive()
{
	return isActive;
}

void Behaviour::Customize(TiXmlElement* element)
{

}

int Behaviour::GetActiveActionsCount() const
{
	return mActiveActions.size();
}

void Behaviour::StopAllActions()
{
	for (ActionList::iterator it = mActiveActions.begin(); it != mActiveActions.end(); ++it)
	{
		(*it)->Stop();
	}
}

EntityPtr Behaviour::GetEntity()
{
	return mActor.lock();
}

void BehaviourDefinition::Parse( TiXmlElement* element )
{

}
