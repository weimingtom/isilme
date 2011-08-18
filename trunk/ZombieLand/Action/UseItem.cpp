#include "ZombieLand.h"
#include "UseItem.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"

namespace action
{
	UseItem::UseItem(inventory::ItemPtr item)
	{
		SetDoingTime(item->GetUsingTime());
		SetEndingTime(item->GetReloadingTime());
		mItem = item;
	}

	UseItem::UseItem(inventory::Item::Slot slot, inventory::InventoryPtr inventory)
	{
		mItem.reset();
		mInventory = inventory;
		mSlot = slot;
	}

	ActionPtr	UseItem::New(inventory::Item::Slot slot, inventory::InventoryPtr inventory)
	{
		return ActionPtr(new UseItem(slot, inventory));
	}

	UseItem::~UseItem()
	{
	}

	void	UseItem::OnStart()
	{
		if (mItem != 0)
		{
			mItem->UseBy(GetActor());
		}
		else
		{
			inventory::ItemPtr item = mInventory->GetSlot(mSlot);
			if (item != 0)
			{
				SetDoingTime(item->GetUsingTime());
				SetEndingTime(item->GetReloadingTime());
				item->UseBy(GetActor());
			}
		}
	}
};