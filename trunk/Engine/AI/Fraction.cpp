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
#include "Fraction.h"
#include "Rank.h"

Fraction::Fraction()
{
}

Fraction::~Fraction()
{
}

std::string Fraction::GetID()
{
	return mID;
}

RankPtr	Fraction::GetRankInfo(int rank)
{
	std::map<int, RankPtr>::iterator it = mRanks.find(rank);
	if (it != mRanks.end())
	{
		return it->second;
	}
	else
		return RankPtr();
}

std::string Fraction::GetName()
{
	return mName;
}

int	Fraction::GetAttitudeTo(FractionPtr fraction)
{
	if (mAttitude.find(fraction) != mAttitude.end())
		return mAttitude[fraction];// - mAgression;
	else if (fraction.get() == this)
		return 100;
	else
		return -GetAgression();
}

void	Fraction::SetAttitudeTo(FractionPtr fraction, int value)
{
	mAttitude[fraction] = value;
}

int		Fraction::GetAgression()
{
	return mAgression;
}