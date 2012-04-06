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
#ifndef ISILME_AI_AIBEHAVIOURDEF_H
#define ISILME_AI_AIBEHAVIOURDEF_H

#include "AITypes.h"
#include "AttributeDef.h"

class ISILME_API AIBehaviourDef
{
public:
	void	Parse(TiXmlElement* element);

	typedef struct FractionInfo
	{
	public:
		std::string id;
		int	rank;
	} FractionInfo;

	typedef std::vector<AttributeDef> AttributesList;
	typedef std::vector<std::string> AIPackageList;
	typedef std::vector<FractionInfo> FractionsList;

	/// Fractions and ranks
	FractionsList fractions;

	/// Definitions of attributes
	AttributesList attributes;

	/// List of AI-packages identifiers
	AIPackageList AIPackages;


private:
	/// Parses attributes from XML
	void	ParseAttributes(TiXmlElement* attributesElement);

	/// Parses AI-packages from XML
	void	ParseAIPackages(TiXmlElement* aiElement);

	/// Parses fractions info
	void	ParseFractions(TiXmlElement* fractionsElement);
};

#endif