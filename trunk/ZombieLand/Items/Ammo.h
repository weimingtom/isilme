#ifndef ZOMBIELAND_ITEMS_AMMO_H
#define ZOMBIELAND_ITEMS_AMMO_H

#include "ZombieLand/Include/Definitions.h"
#include "Engine/Inventory/Item.h"

namespace inventory
{
	class Ammo : public Item
	{
	public:
		Ammo();
		virtual ~Ammo();

		virtual void OnUse(EntityPtr actor);
	};
};

#endif