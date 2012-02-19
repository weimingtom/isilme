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
		TiXmlDocument document(fileName.c_str());
		document.LoadFile();

		MasterFilePtr masterfile = Load(document.RootElement());
		return masterfile;
	}

	MasterFilePtr MasterFileLoader::Load( TiXmlElement* element )
	{
		MasterFilePtr masterFile(new MasterFile());

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
				std::string fileName = std::string("../Data/") + entryElement->GetText();

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

}