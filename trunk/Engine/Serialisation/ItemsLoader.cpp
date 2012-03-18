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