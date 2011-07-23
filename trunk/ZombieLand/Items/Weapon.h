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

		bool	IsInfinity();

		void	SetInfinity(bool flag);

		int		GetAmmo();

		int		GetMaxAmmo();

		void	SetAmmo(int count);

		void	SetMaxAmmo(int count);
	protected:
		int mAmmo;
		int mMaxAmmo;
		bool	isInfinity;
	};

	ItemPtr	CreatePistol();
	ItemPtr	CreateRifle();
};
#endif