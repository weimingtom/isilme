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
#include "Evasion.h"
#include "ISteerable.h"

namespace steering
{


	Evasion::Evasion( VehiclePtr actor, VehiclePtr target ) : 
		mActor(actor),
		mTarget(target)
	{

	}

	Vector2 Evasion::CalcVelocity()
	{
		Vector2 offset = mActor->GetPosition()  - mTarget->GetPosition();
		float distance = offset.Length();
		float timeInterval = std::min(0.1f, distance / mActor->GetMaxVelocity());
		Vector2 v = mActor->GetPosition() - mTarget->PredictFuturePosition(timeInterval); // Inefficient!!!

		v.Normalize();
		v = mActor->GetMaxVelocity() * v;
		v -= mActor->GetVelocity();

		// Limit
		v.Normalize();
		v = mActor->GetMaxVelocity() * v;

		return v;
	}

}