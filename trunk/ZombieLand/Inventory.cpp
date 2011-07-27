#include "ZombieLand.h"
#include "Inventory.h"
#include <algorithm>

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

ItemPtr	Inventory::GetItemByTag(std::string tag)
{
	for (ItemsList::iterator it = mItems.begin(); it != mItems.end(); ++it)
	{
		if ((*it)->GetTag() == tag)
			return *it;
	}

	return ItemPtr();
}

int		Inventory::GetItemsCount()
{
	return mItems.size();
}

ItemPtr	Inventory::GetItem(int number)
{
	return mItems[number];
}

void	Inventory::AddItem(ItemPtr item)
{
	mItems.push_back(item);
	item->mInventory = shared_from_this();
	item->OnAdd();
}

void	Inventory::Unequip(Item::Slot slot)
{
	ItemPtr item = GetSlot(slot);
	if (item != 0)
	{
		mSlots.erase(mSlots.find(slot));
		item->OnUnequip();
	}
}

void	Inventory::Unequip(ItemPtr item)
{
	if (GetSlot(item->GetSlot()) == item)
	{
		mSlots.erase(mSlots.find(item->GetSlot()));
		item->OnUnequip();
	}
}

void	Inventory::Equip(ItemPtr item)
{
	if (std::find(mItems.begin(), mItems.end(), item) == mItems.end())
		AddItem(item);

	Unequip(item->GetSlot());
	mSlots[item->GetSlot()] = item;
	item->OnEquip();
}

ItemPtr	Inventory::GetSlot(Item::Slot slot)
{
	return mSlots[slot];
}