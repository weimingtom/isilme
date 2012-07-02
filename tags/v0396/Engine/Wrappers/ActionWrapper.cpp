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
#include "ActionWrapper.h"

void ActionWrapper::OnStart()
{
	luabind::call_member<void>(this, "OnStart");
}

void ActionWrapper::OnDone()
{
	luabind::call_member<void>(this, "OnDone");
}

void ActionWrapper::OnUpdate( float elapsedTime )
{
	luabind::call_member<void, float>(this, "OnUpdate", elapsedTime);
}

void ActionWrapper::defaultOnStart( Action* base )
{
	base->Action::OnStart();
}

void ActionWrapper::defaultOnUpdate( Action* base, float elapsedTime )
{
	base->Action::OnUpdate(elapsedTime);
}

void ActionWrapper::defaultOnDone( Action* base )
{
	base->Action::OnDone();
}

void ActionWrapper::OnForceStop()
{
	luabind::call_member<void>(this, "OnForceStop");
}

void ActionWrapper::defaultOnForceStop( Action* base )
{
	base->Action::OnForceStop();
}

ActionWrapper::~ActionWrapper()
{

}
