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
#include "ItemsLoader.h"
#include "Core/MasterFile.h"
#include "Core/FactoryManager.h"
#include "Palette/ItemsPalette.h"

namespace serialisation
{
	ItemsLoader::ItemsLoader()
	{

	}

	ItemsLoader::~ItemsLoader()
	{

	}

	EntryPtr ItemsLoader::LoadEntry( std::string filename )
	{
		ContainerEntry<ItemsPalette>* entry = new ContainerEntry<ItemsPalette>(filename);
		entry->data = FactoryManager::GetSingleton()->GetItemsPalette();
		TiXmlDocument document(filename.c_str());
		document.LoadFile();

		TiXmlElement* root = document.RootElement();
		TiXmlElement* defElement = root->FirstChildElement();

		// ��������� ���������� ��� �������� � ���������� �������
		while(defElement)
		{
			inventory::ItemDefPtr def = LoadItem(defElement);

			defElement = defElement->NextSiblingElement();
		}

		return EntryPtr(entry);
	}

	inventory::ItemDefPtr ItemsLoader::LoadItem(TiXmlElement* element)
	{
		inventory::ItemDefPtr def;
		std::string name = element->Attribute("Tag");
		std::string type = element->Value();

		ItemsPalettePtr palette = FactoryManager::GetSingleton()->GetItemsPalette();
		inventory::ItemFactoryPtr factory = palette->GetFactory(type);
		if (factory)
		{
			def = factory->LoadDefinition(element);
			def->Tag = name;
			palette->AddDefinition(def);
		}
		else
		{
			// �����-�� ����, ������� ��������� � �������������������� ����
		}

		return def;
	}
}