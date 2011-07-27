#ifndef ZOMBIELAND_ACTIONS_USEITEM_H
#define ZOMBIELAND_ACTIONS_USEITEM_H

#include "ZombieLand/Include/Definitions.h"
#include "ZombieLand/Item.h"

namespace action
{
	class UseItem : public Action
	{
	public:
		static ActionPtr New(ItemPtr item);
		static ActionPtr New(Item::Slot slot, InventoryPtr inventory);

		UseItem(Item::Slot slot, InventoryPtr inventory);
		UseItem(ItemPtr item);
		virtual ~UseItem();
		virtual void	OnStart();
	protected:
	private:
		ItemPtr	mItem;
		InventoryPtr mInventory;
		Item::Slot mSlot;
	};
};
#endif