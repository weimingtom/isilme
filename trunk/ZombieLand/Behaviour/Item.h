#ifndef ZOMBIELAND_BEHAVIOUR_ITEM_H
#define ZOMBIELAND_BEHAVIOUR_ITEM_H

#include "ZombieLand/Include/Definitions.h"
#include "Activator.h"

namespace behaviour
{
	class ItemDef : public BehaviourDefinition
	{
	public:
		ItemDef();
		virtual ~ItemDef();

		std::string ItemType;
		int	Ammo;

		virtual void	Parse(TiXmlElement* def);
		virtual BehaviourPtr Create();
	protected:
	};

	class Item : public Activator
	{
	public:
		Item(ItemDef* def);
		virtual ~Item();

		virtual void	OnUse(CreaturePtr actor);

		int	GetAmmo();
		void	SetAmmo(int ammo);
	protected:
		std::string	mItemTag;
		int mAmmo;
	};
};
#endif