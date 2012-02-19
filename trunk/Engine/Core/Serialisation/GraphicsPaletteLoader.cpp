#include "IsilmePCH.h"
#include "GraphicsPaletteLoader.h"
#include "../MasterFile.h"
#include "../Palette/GraphicsPalette.h"
#include "FactoryManager.h"

namespace serialisation
{


	GraphicsPaletteLoader::GraphicsPaletteLoader()
	{

	}

	GraphicsPaletteLoader::~GraphicsPaletteLoader()
	{

	}

	EntryPtr GraphicsPaletteLoader::LoadEntry( std::string filename )
	{
		ContainerEntry<GraphicsPalette>* entry = new ContainerEntry<GraphicsPalette>(filename);
		entry->data = FactoryManager::GetSingleton()->GetGraphicsPalette();
		entry->data->Load(filename);
		return EntryPtr(entry);
	}

}