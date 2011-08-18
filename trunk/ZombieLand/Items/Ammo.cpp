#include "ZombieLand.h"
#include "Ammo.h"
#include "Engine/Inventory/Inventory.h"

namespace inventory
{
	AmmoDef::AmmoDef()
	{
	}

	AmmoDef::~AmmoDef()
	{
	}

	ItemPtr	AmmoDef::Create()
	{
		return ItemPtr(new inventory::Ammo(this));
	}

	Ammo::Ammo(AmmoDef* def) : Item(def)
	{
		SetSlot(Item::Ammo);
	}

	Ammo::~Ammo()
	{
	}

	void Ammo::OnUse(EntityPtr actor)
	{
		ItemPtr weapon = GetInventory()->GetSlot(Item::Weapon);
		int needAmmo = weapon->GetMaxAmmo() - weapon->GetAmmo();
		int haveAmmo = min(GetAmmo() + 1, needAmmo);
		if (IsInfinity())
			haveAmmo = needAmmo;

		SetAmmo(GetAmmo() - haveAmmo + 1);
		weapon->SetAmmo(weapon->GetAmmo() + haveAmmo);
	}
};