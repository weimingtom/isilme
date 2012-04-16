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
#include "Arrival.h"
#include "ISteerable.h"

namespace steering
{
	Arrival::Arrival( VehiclePtr actor, const Vector2& target, float slowDistance) : 
		mActor(actor),
		mTarget(target),
		mSlowDistance(slowDistance)
	{

	}

	Vector2 Arrival::CalcVelocity()
	{
		Vector2 targetOffset = mTarget - mActor->GetPosition();
		
		float distance = targetOffset.Length();
		float rampedSpeed = mActor->GetMaxVelocity() * (distance / mSlowDistance);
		float clippedSpeed = std::min(rampedSpeed, mActor->GetMaxVelocity());
		Vector2	desiredVelocity = (clippedSpeed / distance) * targetOffset;
		Vector2 steering = desiredVelocity - mActor->GetVelocity();

		// Limit
		steering.Normalize();
		steering = mActor->GetMaxVelocity() * steering;

		return steering;
	}

}