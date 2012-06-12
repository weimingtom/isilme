#include "ZombieLand.h"
#include "UseItem.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "../Behaviour/Creature.h"
#include "../Behaviour/Item.h"
#include "Definitions.h"

namespace action
{
	UseItem::UseItem(inventory::ItemPtr item)
	{
		SetDuration(item->GetUsingTime() + item->GetReloadingTime());
		//SetEndingTime(item->GetReloadingTime());
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
				SetDuration(item->GetUsingTime() + item->GetReloadingTime());
				//SetEndingTime(item->GetReloadingTime());
				item->UseBy(GetActor());
			}
		}
	}

	bool PickItemPackage::IsApplicable( BehaviourPtr b ) const 
	{
		//behaviour::CreaturePtr c = b->GetEntity()->As<behaviour::Creature>();
		behaviour::ActivatorPtr activator = behaviour::Activator::GetActivatorFor(b->GetEntity());

		mTarget = boost::shared_dynamic_cast<behaviour::Item>(activator);

		return mTarget != nullptr;
	}

	PickItem::PickItem( behaviour::ItemPtr it )
	{
		mItem = it;
		SetDuration(0.1f);
	}

	void PickItem::OnStart()
	{
		mItem->UseBy(GetEntity()->As<behaviour::Creature>());
	}

	ActionPtr PickItemPackage::CreateAction() const
	{
		return ActionPtr( new PickItem(mTarget));
	}

	void PickItemPackageDef::Parse( TiXmlElement* element )
	{

	}

	AIPackagePtr PickItemPackageDef::CreatePackage()  
	{
		return AIPackagePtr(new PickItemPackage());
	}

};