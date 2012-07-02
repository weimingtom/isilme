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
#include "Core/FactoryManager.h"
#include "FractionsLoader.h"
#include "../Palette/Types.h"
#include "../Palette/FractionsPalette.h"
#include "AI/Fraction.h"
#include "AI/Rank.h"
#include "Core/MasterFile.h"

namespace serialisation
{

	FractionsLoader::FractionsLoader()
	{

	}

	FractionsLoader::~FractionsLoader()
	{

	}

	EntryPtr FractionsLoader::LoadEntry( std::string filename )
	{
		ContainerEntry<FractionsPalette>* entry = new ContainerEntry<FractionsPalette>(filename);
		entry->data = FactoryManager::GetSingleton()->GetFractionsPalette();

		TiXmlDocument document(filename.c_str());
		document.LoadFile();

		LoadFractions(document.RootElement());

		return EntryPtr(entry);
	}

	void FractionsLoader::LoadFractions( TiXmlElement* element )
	{
		FractionsPalettePtr palette = FactoryManager::GetSingleton()->GetFractionsPalette();

		std::map<std::pair<std::string, std::string>, int> relations;
		// ��������� �������
		TiXmlElement* fractionElement = element->FirstChildElement("Fraction");
		
		while (fractionElement)
		{
			// ������ ���������
			const char* idAttr = fractionElement->Attribute("ID");
			const char* nameAttr = fractionElement->Attribute("Name");
		
			if (idAttr)
			{
				FractionPtr fraction(new Fraction());
		
				// ������������� �������
				fraction->mID = idAttr;
		
				// �������� �������
				fraction->mName = nameAttr ? nameAttr : "";
		
				// �������������
				fraction->mAgression = 0;
				fractionElement->QueryIntAttribute("Agression", &(fraction->mAgression));
		
				// �����
				TiXmlElement* rankElement = fractionElement->FirstChildElement("Rank");
				while (rankElement)
				{
					int rankID = 0;
					rankElement->QueryIntAttribute("ID", &rankID);
		
					if (rankID)
					{
						RankPtr rank(new Rank());
						rank->mID = rankID;
		
						fraction->mRanks[rankID] = rank;
					}
					else
					{
						LOG_W("Rank of %s fraction has no ID", idAttr);
					}
					rankElement = rankElement->NextSiblingElement("Rank");
				}
		
				// ���������
				TiXmlElement* attitudeElement = fractionElement->FirstChildElement("Attitude");
				while (attitudeElement)
				{
					const char* otherFraction = attitudeElement->Attribute("Fraction");
					int attitude = 0;
					attitudeElement->QueryIntAttribute("Value", &attitude);
		
					if (otherFraction)
					{
						relations[std::pair<std::string, std::string>(fraction->GetID(), otherFraction)] = attitude;
					}
		
					attitudeElement = attitudeElement->NextSiblingElement("Attitude");
				}
		
				// ���������� �������
				palette->AddFraction(fraction);
			}
			else
			{
				LOG_W("Fraction has no ID");
			}
		
			fractionElement = fractionElement->NextSiblingElement("Fraction");
		}
		
		// ��������� ��������� ����� ���������
		for (std::map<std::pair<std::string, std::string>, int>::iterator it = relations.begin(); it != relations.end(); ++it)
		{
			FractionPtr f1 = palette->GetFraction(it->first.first);
			FractionPtr f2 = palette->GetFraction(it->first.second);
		
			if (!f2)
			{
				LOG_W("Cannot set attitude to %s. Fraction doesn\'t exist", it->first.second.c_str());
			}
			else
			{
				f1->SetAttitudeTo(f2, it->second);
			}
		}
	}

}