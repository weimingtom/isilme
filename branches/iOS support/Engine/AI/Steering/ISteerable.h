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
#ifndef ISILME_AI_STEERING_ISTEERABLE_H
#define ISILME_AI_STEERING_ISTEERABLE_H

#include "SteeringTypes.h"

/// @interface ISteerable
/// Interface for object that can implement steering behaviour
class ISILME_API IVehicle
{
public:
	virtual ~IVehicle() {};

	/// Sets maximum acceleration
	virtual void SetMaxAcceleration(float maxAcceleration) = 0;

	/// Gets maximum acceleration
	virtual float GetMaxAcceleration() const = 0;

	/// Gets possible position in the future
	virtual Vector2 PredictFuturePosition(const float predictionTime) const = 0;

	/// Gets current position
	virtual Vector2 GetPosition() const = 0;

	/// Gets maximum velocity
	virtual float GetMaxVelocity() const = 0;

	/// Gets current velocity
	virtual Vector2 GetVelocity() const = 0;

	/// Gets nearest object in direction
	///
	/// @param		direction vector
	/// @param		maxDistance vector length
	virtual VehiclePtr	RayQuery(const Vector2 direction, float maxDistance) = 0;
};

#endif