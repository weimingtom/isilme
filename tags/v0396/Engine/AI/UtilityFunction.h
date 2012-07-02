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
#ifndef ISILME_AI_UTILITYFUNCTION_H
#define ISILME_AI_UTILITYFUNCTION_H

#include "Definitions.h"
#include "AITypes.h"

/// @class UtilityFunction
class ISILME_API UtilityFunction
{
public:
	virtual ~UtilityFunction();

	/// Calculates utility value
	virtual float Calculate(BehaviourPtr behaviour) const = 0;

private:

};


class ISILME_API WeightUtilityFunction : public UtilityFunction
{
public:
	WeightUtilityFunction();
	virtual ~WeightUtilityFunction();

	virtual float Calculate(BehaviourPtr behaviour) const override;

	/// Adds perception to utility-function
	void AddPerception(PerceptionPtr perception, float weight);
private:
	/// @struct PerceptionInfo
	/// Internal container for weights of perceptions
	struct PerceptionInfo
	{
		/// Perception
		PerceptionPtr perception;

		/// Weight
		float weight;
	};

	typedef std::vector<PerceptionInfo> PIVector;

	/// Perceptions
	PIVector mPerceptions;

};
#endif