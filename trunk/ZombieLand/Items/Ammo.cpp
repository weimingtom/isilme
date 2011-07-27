#include "ZombieLand.h"
#include "Ammo.h"
#include "ZombieLand/Inventory.h"

namespace items
{
	Ammo::Ammo()
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
		int haveAmmo = min(GetAmmo(), needAmmo);
		if (IsInfinity())
			haveAmmo = needAmmo;

		weapon->SetAmmo(weapon->GetAmmo() + haveAmmo);
	}
};