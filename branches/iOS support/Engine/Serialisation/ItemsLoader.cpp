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
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
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

		// Загружаем поочередно все элементы с описаниями графики
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
			// Какой-то хлам, вывести сообщение о незарегистрированном типе
		}

		return def;
	}
}