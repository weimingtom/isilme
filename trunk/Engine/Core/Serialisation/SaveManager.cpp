#include "IsilmePCH.h"
#include "SaveManager.h"
#include "SaveData.h"

namespace serialisation
{
	SaveManagerPtr SaveManager::mInstance;

	SaveManager::SaveManager()
	{

	}

	SaveManager::~SaveManager()
	{
	
	}

	serialisation::SaveManagerPtr SaveManager::GetSingleton()
	{
		if (!mInstance)
			mInstance = SaveManagerPtr(new SaveManager());
		return mInstance;
	}

	serialisation::SaveDataPtr SaveManager::CreateSaveData()
	{
		return SaveDataPtr(new SaveData());
	}

	void SaveManager::LoadSaveData()
	{
		mQuickSave.reset(new SaveData());
	}

	int SaveManager::GetSaveCount()
	{
		return mSaves.size();
	}

	SaveDataPtr SaveManager::GetSaveData( int index )
	{
		return mSaves.at(index);
	}

	SaveDataPtr SaveManager::GetAutoSave()
	{
		return mAutoSave;
	}

	SaveDataPtr SaveManager::GetQuickSave()
	{
		return mQuickSave;
	}

	std::string SaveManager::GetSaveFolder()
	{
		return "../Saves";
	}

};