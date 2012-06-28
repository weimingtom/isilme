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
#ifndef ISILME_AI_ACTUATOR_H
#define ISILME_AI_ACTUATOR_H

#include "AITypes.h"

class Actuator
{
public:
	/// Constructor
	///
	/// @param		id	Identifier of the actuator. Should be unique
	Actuator(std::string id);

	/// Gets identifier of the actuator
	std::string	GetID() const;

	/// Gets if the actuator is locked
	bool IsLocked() const;

	/// Makes actuator busy by an action
	///
	/// @param action an action
	/// @param force  true if need to stop current action
	/// 
	/// @return true, if action is locked
	bool LockByAction(ActionPtr action, bool force = false);

	/// Makes actuator free
	/// If actuator is locked
	void Unlock();

	/// Updates actuator state
	void Update(float elapsedTime);
private:
	/// Action that own actuator
	ActionPtr	mOwner;

	/// Identifier
	std::string mID;
};
#endif