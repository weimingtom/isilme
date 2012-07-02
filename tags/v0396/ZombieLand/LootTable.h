#ifndef ZOMBIELAND_LOOTTABLE_H
#define ZOMBIELAND_LOOTTABLE_H

#include "Definitions.h"

class Loot
{
public:
	std::string Item;
	int Ammo;
};

class LootRecord
{
public:
	LootRecord();

	std::string Item;
	int MaxAmmo;
	int MinAmmo;
};

class LootTable
{
public:
	LootTable();
	virtual ~LootTable();

	/// Загружает таблицу лута
	static LootTablePtr Load(TiXmlElement* def);

	/// Генерирует лут
	void GenerateLoot(std::list<Loot>* lootList);
private:
	std::list<LootRecord> mTable;
	float mChance;
};

class LootManager
{
public:
	LootManager();
	virtual ~LootManager();

	static LootManager* GetSingleton();

	/// Загружает таблицы из файла
	void	Load(std::string fileName);

	/// Очищает таблицы
	void	Clear();

	/// Возвращает таблицу предметов
	LootTablePtr	GetLootTable(std::string name);
private:
	LootMap mLootTables;
	static LootManager* mInstance;
};

#endif