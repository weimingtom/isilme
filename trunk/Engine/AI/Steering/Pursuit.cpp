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
#include "Pursuit.h"
#include "ISteerable.h"

namespace steering
{

	Pursuit::Pursuit( VehiclePtr actor, VehiclePtr target ) : 
		mTarget(target),
		mActor(actor)
	{

	}

	Vector2 Pursuit::CalcVelocity()
	{
		Vector2 offset = mTarget->GetPosition()  - mActor->GetPosition();
		float distance = offset.Length();
		float timeInterval = std::min(0.1f, distance / mActor->GetMaxVelocity());
		Vector2 v = mTarget->PredictFuturePosition(timeInterval) - mActor->GetPosition();

		if (v.LengthSquared() < 1E-6)
			return Vector2(0.0f, 0.0f);

		v.Normalize();
		v = mActor->GetMaxVelocity() * v;
		v -= mActor->GetVelocity();

		// Limit
		v.Normalize();
		v = mActor->GetMaxVelocity() * v;

		return v;
	}

}