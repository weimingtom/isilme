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

	Ammo = -1;
	element->QueryIntAttribute("Ammo", &Ammo);
}
BehaviourPtr ItemDef::Create()
{
	Item* item = new Item(this);
	return BehaviourPtr(item);
}
Item::Item(ItemDef* def) : Activator(def)
{
	mItemTag = def->ItemType;
	mAmmo = def->Ammo;
}
Item::~Item()
{
}
int		Item::GetAmmo()
{
	return mAmmo;
}

void	Item::SetAmmo(int ammo)
{
	mAmmo = ammo;
}
void	Item::OnUse(CreaturePtr actor)
{
	if (mItemTag == "")
		return;

	inventory::ItemPtr item = FactoryManager::GetSingleton()->CreateItem(mItemTag);
	if (mAmmo == -1)
		item->SetAmmo(item->GetMaxAmmo());
	else
		item->SetAmmo(mAmmo);

	actor->GetInventory()->AddItem(item);
	GetActor()->Remove();

	//if (actor->GetInventory()->GetSlot(item->GetSlot()) == 0)
	//actor->GetInventory()->Equip(item);
}
};

