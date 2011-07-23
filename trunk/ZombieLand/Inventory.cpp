#include "ZombieLand.h"
#include "Inventory.h"

InventoryPtr Inventory::New()
{
	Inventory* i = new Inventory();
	return InventoryPtr(i);
}

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void	Inventory::AddItem(ItemPtr item)
{
	mItems.insert(item);
}

void	Inventory::Equip(ItemPtr item)
{
	if (mItems.find(item) == mItems.end())
		AddItem(item);

	mSlots[item->GetSlot()] = item;
	
}

ItemPtr	Inventory::GetSlot(Item::Slot slot)
{
	return mSlots[slot];
}