#ifndef ITEMS_WEAPON_H
#define ITEMS_WEAPON_H

#include "ZombieLand/Include/Definitions.h"
#include "ZombieLand/Item.h"

namespace items
{
	class Weapon : public Item
	{
	public:
		Weapon();
		virtual ~Weapon();

		virtual void	OnUse(EntityPtr actor);
		virtual void	OnAdd();
		virtual void	OnEquip();

		void	SetAmmoTag(std::string ammoTag);
	private:
		std::string mAmmoTag;
	};

	ItemPtr	CreatePistol();
	ItemPtr	CreateRifle();
	ItemPtr	CreateItem(std::string tag);
};
#endif