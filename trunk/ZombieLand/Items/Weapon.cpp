#include "ZombieLand.h"
#include "ZombieLand/Inventory.h"
#include "Weapon.h"
#include "Ammo.h"
#include "Spell.h"
#include "ZombieLand/Behaviour/Bullet.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"

namespace items
{
	Weapon::Weapon()
	{
		SetSlot(Item::Weapon);
		SetMaxAmmo(10);
		SetAmmo(10);
		SetInfinity(false);
	}

	Weapon::~Weapon()
	{
	}

	ItemPtr	CreatePistol()
	{
		Weapon* w = new Weapon();
		w->SetInfinity(false);
		w->SetMaxAmmo(15);
		w->SetAmmo(15);
		w->SetUseSound("../Data/Sounds/Weapons/Gun.wav");
		w->SetUsingTime(0.1f);
		w->SetReloadingTime(0.3f);
		w->SetIcon("../Data/Icons/Weapons/Gun.png");
		w->SetAmmoTag("PistolAmmo");

		return ItemPtr(w);
	}

	void	Weapon::OnAdd()
	{
		ItemPtr w = GetInventory()->GetSlot(Item::Weapon);
		
		bool f = w != 0;
		if (w != 0)
			f = w->GetAmmo() > 0 || w->IsInfinity();

		if (!f)
			GetInventory()->Equip(shared_from_this());
	}

	void	Weapon::OnEquip()
	{
		ItemPtr ammo = GetInventory()->GetItemByTag(mAmmoTag);
		if (ammo == 0)
		{
			ammo = CreateItem(mAmmoTag);
		}
		GetInventory()->Equip(ammo);
	}

	void	Weapon::OnUse(EntityPtr actor)
	{
		EntityPtr bullet = FactoryManager::GetSingleton()->CreateEntity("Bullet", "", actor->GetLevel());
		bullet->SetAngle(actor->GetAngle());
		bullet->SetPosition(actor->GetPosition().x, actor->GetPosition().y);

		(boost::shared_dynamic_cast<behaviour::Bullet, Behaviour>(bullet->GetBehaviour()))->SetGunslinger(actor->GetBehaviour());
		actor->GetLevel()->GetLayer("Bullets")->Add(bullet);
	}

	void	Weapon::SetAmmoTag(std::string ammoTag)
	{
		mAmmoTag = ammoTag;
	}

	ItemPtr	CreateRifle()
	{
		Weapon* w = new Weapon();
		w->SetInfinity(false);
		w->SetMaxAmmo(360);
		w->SetAmmo(30);
		w->SetUseSound("../Data/Sounds/Weapons/Gun.wav");
		w->SetUsingTime(0.1f);
		w->SetReloadingTime(0.1f);
		w->SetIcon("../Data/Icons/Weapons/AK47.png");

		return ItemPtr(w);
	}

	ItemPtr	CreateAK47()
	{
		Weapon* w = new Weapon();
		w->SetInfinity(false);
		w->SetMaxAmmo(40);
		w->SetAmmo(40);
		w->SetUseSound("../Data/Sounds/Weapons/Gun.wav");
		w->SetUsingTime(0.1f);
		w->SetReloadingTime(0.1f);
		w->SetIcon("../Data/Icons/Weapons/AK47.png");
		w->SetAmmoTag("AK47Ammo");
		return ItemPtr(w);
	}

	ItemPtr CreatePistolAmmo()
	{
		Ammo* a = new Ammo();
		a->SetInfinity(true);
		//w->SetUseSound("../Data/Sounds/Weapons/Gun.wav");
		a->SetUsingTime(0.5f);
		a->SetReloadingTime(0.0f);
		//w->SetIcon("../Data/Icons/Weapons/Gun.png");

		return ItemPtr(a);
	}

	ItemPtr CreateAK47Ammo()
	{
		Ammo* a = new Ammo();
		a->SetInfinity(false);
		a->SetMaxAmmo(360);
		a->SetAmmo(360);
		//w->SetUseSound("../Data/Sounds/Weapons/Gun.wav");
		a->SetUsingTime(0.5f);
		a->SetReloadingTime(0.0f);
		//w->SetIcon("../Data/Icons/Weapons/Gun.png");

		return ItemPtr(a);
	}

	ItemPtr	CreateHealSpell()
	{
		Spell* s = new Spell();
		s->SetInfinity(true);
		s->SetAction(ActionPtr(new action::Heal()));
		s->SetIcon("../Data/Icons/Spells/Heal.png");

		return ItemPtr(s);
	}

	ItemPtr	CreateWindSpell()
	{
		Spell* s = new Spell();
		s->SetInfinity(true);
		s->SetAction(ActionPtr(new action::Wind()));
		s->SetIcon("../Data/Icons/Spells/Wind.png");

		return ItemPtr(s);
	}

	ItemPtr	CreateShildSpell()
	{
		Spell* s = new Spell();
		s->SetInfinity(true);
		s->SetAction(ActionPtr(new action::Shild()));
		s->SetIcon("../Data/Icons/Spells/Shild.png");
		s->SetContinuous(true);

		return ItemPtr(s);
	}

	ItemPtr	CreateItem(std::string tag)
	{
		ItemPtr item;
		if (tag == "Pistol")
			item = CreatePistol();
		else if (tag == "Rifle")
			item = CreateRifle();
		else if (tag == "AK47")
			item = CreateAK47();
		else if (tag == "PistolAmmo")
			item = CreatePistolAmmo();
		else if (tag == "AK47Ammo")
			item = CreateAK47Ammo();
		else if (tag == "HealSpell")
			item = CreateHealSpell();
		else if (tag == "WindSpell")
			item = CreateWindSpell();
		else if (tag == "ShildSpell")
			item = CreateShildSpell();
		else
			item = ItemPtr();

		if (item != 0)
			item->SetTag(tag);

		return item;
	}
};