#include "ZombieLand.h"
#include "UseItem.h"
#include "ZombieLand/Item.h"
#include "ZombieLand/Inventory.h"

namespace action
{
	UseItem::UseItem(ItemPtr item)
	{
		SetDoingTime(item->GetUsingTime());
		SetEndingTime(item->GetReloadingTime());
		mItem = item;
	}

	UseItem::UseItem(Item::Slot slot, InventoryPtr inventory)
	{
		mItem.reset();
		mInventory = inventory;
		mSlot = slot;
	}

	ActionPtr	UseItem::New(Item::Slot slot, InventoryPtr inventory)
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
			ItemPtr item = mInventory->GetSlot(mSlot);
			if (item != 0)
			{
				SetDoingTime(item->GetUsingTime());
				SetEndingTime(item->GetReloadingTime());
				item->UseBy(GetActor());
			}
		}
	}
};