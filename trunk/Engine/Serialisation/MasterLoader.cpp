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
#include "MasterLoader.h"
#include "Core/MasterFile.h"
#include "LevelLoader.h"
#include "ConversationLoader.h"
#include "EntityPaletteLoader.h"
#include "GraphicsPaletteLoader.h"
#include "AIPaletteLoader.h"
#include "ScriptLoader.h"
#include "FractionsLoader.h"
#include "ItemsLoader.h"
#include "StoryLoader.h"
#include "Core/FactoryManager.h"
#include "Core/ResourceManager.h"

namespace serialisation
{
	MasterFileLoader::MasterFileLoader()
	{
		Add("Levels", EntryLoaderPtr(new LevelLoader()));
		Add("Conversations", EntryLoaderPtr(new ConversationLoader()));
		Add("Graphics", EntryLoaderPtr(new GraphicsPaletteLoader()));
		Add("Entities", EntryLoaderPtr(new EntityPaletteLoader()));
		Add("AIPackages", EntryLoaderPtr(new AIPaletteLoader()));
		Add("Scripts", EntryLoaderPtr(new ScriptLoader()));
		Add("Fractions", EntryLoaderPtr(new FractionsLoader()));
		Add("Items", EntryLoaderPtr(new ItemsLoader()));
		Add("Story", EntryLoaderPtr(new StoryLoader()));
	}

	MasterFileLoader::~MasterFileLoader()
	{

	}

	void MasterFileLoader::Add( std::string category, EntryLoaderPtr loader )
	{
		mLoaders[category] = loader;
	}

	MasterFilePtr MasterFileLoader::Load( std::string fileName )
	{
        const char* absPath = Engine::GetSingleton()->GetResourceManager()->ResourcePath(fileName.c_str());
		TiXmlDocument document(absPath);
        
		document.LoadFile();

		MasterFilePtr masterfile = Load(document.RootElement());
		return masterfile;
	}

	MasterFilePtr MasterFileLoader::Load( TiXmlElement* element )
	{
		MasterFilePtr masterFile = FactoryManager::GetSingleton()->GetMasterFile();

		TiXmlElement* categoryElement = element->FirstChildElement();
		while (categoryElement)
		{
			CategoryPtr ctg = LoadCategory(categoryElement);
			masterFile->AddCategory(ctg);

			categoryElement = categoryElement->NextSiblingElement();
		}

		return masterFile;
	}

	CategoryPtr MasterFileLoader::LoadCategory( TiXmlElement* categoryElement )
	{
		std::string loaderType = categoryElement->Value();
		CategoryPtr category(new Category(loaderType));
		EntryLoaderPtr loader = mLoaders[loaderType];

		if (loader)
		{
			TiXmlElement* entryElement = categoryElement->FirstChildElement("File");
			while (entryElement)
			{
				std::string fileName = entryElement->GetText();

				EntryPtr entry = loader->LoadEntry(fileName);
				category->Add(entry);

				entryElement = entryElement->NextSiblingElement("File");
			}
		}
		else
		{
			// Loader is not found
		}
		return category;
	}


	MasterFileSerialiser::MasterFileSerialiser()
	{

	}

	MasterFileSerialiser::~MasterFileSerialiser()
	{

	}

	void MasterFileSerialiser::Serialise( MasterFilePtr data, std::string filename )
	{
		TiXmlElement root("DataFile");
		TiXmlDocument document(filename.c_str());

		for (int i = 0; i < data->GetSize(); ++i)
		{
			CategoryPtr category = data->GetCategoryAt(i);
			TiXmlElement categoryElement(category->GetName().c_str());

			for (int j = 0; j < category->GetSize(); ++j)
			{
				TiXmlElement entryElement("File");
				entryElement.InsertEndChild(TiXmlText(category->GetEntry(j)->GetFileName().c_str()));
				categoryElement.InsertEndChild(entryElement);
			}
			root.InsertEndChild(categoryElement);
		}

		document.InsertEndChild(root);
		document.SaveFile();

	}

}
