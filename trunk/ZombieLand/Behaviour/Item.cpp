#include "ZombieLand.h"
#include "Item.h"
#include "Creature.h"
#include "ZombieLand/Items/Weapon.h"

namespace behaviour 
{
ItemDef::ItemDef()
{
	ItemType = "";
}
ItemDef::~ItemDef()
{
}
void	ItemDef::Parse(TiXmlElement* element)
{
	if (element->Attribute("ItemType") != 0)
		ItemType = element->Attribute("ItemType");
}
BehaviourPtr ItemDef::Create()
{
	Item* item = new Item(this);
	return BehaviourPtr(item);
}
Item::Item(ItemDef* def)
{
	mItemTag = def->ItemType;
}
Item::~Item()
{
}
void	Item::OnUse(CreaturePtr actor)
{
	if (mItemTag == "")
		return;

	ItemPtr item = items::CreateItem(mItemTag);
	actor->GetInventory()->AddItem(item);
	GetActor()->Remove();

	//if (actor->GetInventory()->GetSlot(item->GetSlot()) == 0)
	//actor->GetInventory()->Equip(item);
}
};

