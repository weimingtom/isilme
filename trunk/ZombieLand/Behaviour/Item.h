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
	protected:
		std::string	mItemTag;
	private:
	};
};
#endif