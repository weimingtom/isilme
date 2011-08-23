#include "ZombieLand.h"
#include "LootTable.h"

LootManager* LootManager::mInstance = 0;

LootRecord::LootRecord()
{
	Item = "";
	MaxAmmo = 0;
	MinAmmo = 0;
}

LootTable::LootTable()
{
}

LootTable::~LootTable()
{
}

LootTablePtr LootTable::Load(TiXmlElement* def)
{
	LootTablePtr lootTable(new LootTable());

	TiXmlElement* lootElement = def->FirstChildElement("Loot");

	while (lootElement)
	{
		LootRecord record;
		
		lootElement->QueryIntAttribute("MaxAmmo", &record.MaxAmmo);
		lootElement->QueryIntAttribute("MinAmmo", &record.MinAmmo);

		if (lootElement->Attribute("Item"))
			record.Item = lootElement->Attribute("Item");

		lootTable->mTable.push_back(record);

		lootElement = lootElement->NextSiblingElement("Loot");
	}

	return lootTable;
}

void	LootTable::GenerateLoot(std::list<Loot>* lootList)
{
}

LootManager::LootManager()
{
}

LootManager::~LootManager()
{
}

LootManager*	LootManager::GetSingleton()
{
	if (!mInstance)
		mInstance = new LootManager();
	return mInstance;
}

LootTablePtr LootManager::GetLootTable(std::string name)
{
	LootMap::iterator it = mLootTables.find(name);
	if (it != mLootTables.end())
		return it->second;
	else
		return LootTablePtr();
}

void	LootManager::Load(std::string fileName)
{
	TiXmlDocument* document = new TiXmlDocument();
	document->LoadFile(fileName.data());

	TiXmlElement* root = document->RootElement();

	TiXmlElement* tableElement = root->FirstChildElement("Table");

	while (tableElement)
	{
		std::string name = tableElement->Attribute("Name");
		LootTablePtr table = LootTable::Load(tableElement);
		mLootTables[name] = table;
	}

	delete document;
}