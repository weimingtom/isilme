#ifndef ZOMBIELAND_ITEMS_SPELL_H
#define ZOMBIELAND_ITEMS_SPELL_H

#include "ZombieLand/Include/Definitions.h"
#include "Engine/Inventory/Item.h"
#include "ZombieLand/Items/Spell.h"

namespace inventory
{
	class Spell : public Item
	{
	public:
		Spell();
		virtual ~Spell();

		void	SetAction(ActionPtr action);

		virtual void OnUse(EntityPtr actor);

		bool	IsContinuous();

		void	SetContinuous(bool flag);
	private:
		bool	isContinuous;
		ActionPtr mAction;
	};
};
#endif