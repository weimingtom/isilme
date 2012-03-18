#include "ZombieLand.h"
#include "Container.h"
#include "../LootTable.h"

Container::Container()
{

}

Container::~Container()
{

}

void Container::Init( ContainerDef* def )
{
	/// Инвентарь
	mInventory = inventory::Inventory::New();
	for (ContainerDef::ItemsList::iterator it = def->items.begin(); it != def->items.end(); ++it)
	{
		inventory::ItemPtr item = FactoryManager::GetSingleton()->CreateItem(it->tag);
		if (item)
		{
			item->SetAmmo(it->ammo);
			mInventory->AddItem(item);
			if (it->equip)
				mInventory->Equip(item);
		}
		else
		{

		}
	}
}

LootTablePtr Container::GetLootTable() const
{
	return LootManager::GetSingleton()->GetLootTable(mLoot);
}

inventory::InventoryPtr Container::GetInventory() const
{
	return mInventory;
}

void ContainerDef::Parse( TiXmlElement* element )
{		
	/// Загружаем инвентарь
	TiXmlElement* inventoryElement = element->FirstChildElement("Inventory");
	ParseInventory(inventoryElement);

	/// Загружаем таблицу лута
	if (element->Attribute("Loot"))
		loot = element->Attribute("Loot");

}

void ContainerDef::ParseInventory(TiXmlElement* inventoryELement)
{
	if (!inventoryELement)
		return;

	TiXmlElement* itemElement = inventoryELement->FirstChildElement("Item");
	while (itemElement)
	{
		const char* tagAttr = itemElement->Attribute("Tag");
		if (tagAttr)
		{
			ItemInfo item;
			item.tag = tagAttr;
			item.ammo = 1;

			itemElement->QueryIntAttribute("Ammo", &item.ammo);
			int equip = 0;
			itemElement->QueryIntAttribute("Equip", &equip);
			item.equip = equip != 0;

			items.push_back(item);
		}

		itemElement = itemElement->NextSiblingElement("Item");
	}
}
