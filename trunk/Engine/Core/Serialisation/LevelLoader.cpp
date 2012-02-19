#include "IsilmePCH.h"
#include "LevelLoader.h"
#include "Level.h"
#include "Core/MasterFile.h"
namespace serialisation
{


	LevelLoader::LevelLoader()
	{

	}

	LevelLoader::~LevelLoader()
	{

	}

	EntryPtr LevelLoader::LoadEntry( std::string filename )
	{
		LevelEntry* entry = new LevelEntry(filename);
		LevelPtr level = LoadLevel(filename);
		entry->data = level;
		return EntryPtr(entry);
	}

	LevelPtr LevelLoader::LoadLevel( std::string filename )
	{
		return Level::Load(filename);
	}

}