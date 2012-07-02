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
#ifndef ISILME_FRACTION_H
#define ISILME_FRACTION_

#include "Definitions.h"
#include "../Serialisation/Types.h"

///
class ISILME_API Fraction
{
	friend class FactoryManager;
	friend class serialisation::FractionsLoader;
public:
	Fraction();
	virtual ~Fraction();

	/// ���������� ���������� � �����
	RankPtr	GetRankInfo(int rank);

	/// ���������� ������������� �������
	std::string GetID();

	/// ���������� �������� �������
	std::string GetName();

	/// ���������� ��������� � �������
	int	GetAttitudeTo(FractionPtr fraction);

	/// ������������� ��������� � ������ �������
	void SetAttitudeTo(FractionPtr fraction, int value);

	/// ���������� ����� ������������� �������
	int GetAgression();

	/// ���������� ����� �������������
	void SetAgression(int value);
private:
	int mAgression;
	std::string mID;
	std::string mName;
	std::map<int, RankPtr> mRanks;
	std::map<FractionPtr, int> mAttitude;
};
#endif