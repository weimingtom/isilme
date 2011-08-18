#ifndef ITEMS_WEAPON_H
#define ITEMS_WEAPON_H

#include "ZombieLand/Include/Definitions.h"
#include "Engine/Inventory/Item.h"

namespace inventory
{
	class WeaponDef : public ItemDef
	{
	public:
		WeaponDef();
		virtual ~WeaponDef();

		virtual ItemPtr Create();
		virtual void Parse(TiXmlElement* def);
		std::string AmmoTag;
	};

	class Weapon : public inventory::Item
	{
	public:
		Weapon(WeaponDef* def);
		virtual ~Weapon();

		virtual void	OnUse(EntityPtr actor);
		virtual void	OnAdd();
		virtual void	OnEquip();

		void	SetAmmoTag(std::string ammoTag);
	private:
		std::string mAmmoTag;
	};

	inventory::ItemPtr	CreateItem(std::string tag);
};
#endif