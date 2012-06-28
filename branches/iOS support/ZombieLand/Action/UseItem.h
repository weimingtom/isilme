#ifndef ZOMBIELAND_ACTIONS_USEITEM_H
#define ZOMBIELAND_ACTIONS_USEITEM_H

#include "../Definitions.h"
#include "../AI/AIPackage.h"

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

	class PickItem : public Action
	{
	public:
		PickItem(behaviour::ItemPtr it);

		virtual void OnStart() override;
	private:
		behaviour::ItemPtr mItem;
	};

	class PickItemPackage : public AIPackage
	{
	public:
		virtual bool IsApplicable(BehaviourPtr behaviour) const override;

		virtual ActionPtr CreateAction() const override;
	private:
		mutable behaviour::ItemPtr mTarget;
	};

	class PickItemPackageDef : public AIPackageDef
	{
	public:
		virtual void Parse(TiXmlElement* element) override;

		virtual AIPackagePtr CreatePackage() override;
	};
};
#endif