#ifndef ZOMBIELAND_BEHAVIOUR_CONTAINER_H
#define ZOMBIELAND_BEHAVIOUR_CONTAINER_H

#include "../Definitions.h"

/// @interface IContainer
class IContainer
{
public:
	virtual ~IContainer() {};

	/// Gets content of the container
	virtual inventory::InventoryPtr	GetInventory() const = 0;

	virtual LootTablePtr GetLootTable() const = 0;
};

/// @class ContainerDef
/// Defines container and it's content
class ContainerDef
{
public:
	typedef struct ItemInfo
	{
	public:
		std::string tag;
		int			ammo;
		bool		equip;
	} ItemInfo;
	typedef std::list<ItemInfo>	ItemsList;

	/// Items in container
	ItemsList items;

	/// Parses XML element
	void Parse(TiXmlElement* element);

	void ParseInventory(TiXmlElement* inventoryELement);

	std::string loot;
};

/// @class Container
/// Simple implementation for container
class Container : public IContainer
{
public:
	Container();
	virtual ~Container();

	/// Initiate data
	void Init(ContainerDef* def);

	virtual inventory::InventoryPtr	GetInventory() const;

	/// Таблица выпадающих предметов 
	virtual LootTablePtr GetLootTable() const;

private:
	std::string mLoot;
	inventory::InventoryPtr	mInventory;
};
#endif