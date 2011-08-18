#ifndef ZOMBIELAND_ACTIONS_USEITEM_H
#define ZOMBIELAND_ACTIONS_USEITEM_H

#include "ZombieLand/Include/Definitions.h"
#include "Engine/Inventory/Item.h"

namespace action
{
	class UseItem : public Action
	{
	public:
		static ActionPtr New(inventory::ItemPtr item);
		static ActionPtr New(inventory::Item::Slot slot, inventory::InventoryPtr inventory);

		UseItem(inventory::Item::Slot slot, inventory::InventoryPtr inventory);
		UseItem(inventory::ItemPtr item);
		virtual ~UseItem();
		virtual void	OnStart();
	protected:
	private:
		inventory::ItemPtr	mItem;
		inventory::InventoryPtr mInventory;
		inventory::Item::Slot mSlot;
	};
};
#endif