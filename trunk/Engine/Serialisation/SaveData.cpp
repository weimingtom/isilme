#include "IsilmePCH.h"
#include "SaveData.h"
#include "SaveManager.h"

namespace serialisation
{


	SaveData::SaveData()
	{

	}

	SaveData::~SaveData()
	{

	}

	std::string SaveData::GetName()
	{
		return mName;
	}

	time_t SaveData::GetTime()
	{
		return mTime;
	}

	void SaveData::SetName( std::string value )
	{
		mName = value;
	}

	std::string SaveData::GetFullPath()
	{
		return SaveManager::GetSingleton()->GetSaveFolder() + "/" + mName + ".sav";
	}

};