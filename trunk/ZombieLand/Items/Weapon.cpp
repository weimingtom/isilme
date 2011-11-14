#include "ZombieLand.h"
#include "Engine/Inventory/Inventory.h"
#include "Weapon.h"
#include "Ammo.h"
#include "Spell.h"
#include "ZombieLand/Behaviour/Bullet.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"

namespace inventory
{
	WeaponDef::WeaponDef()
	{
	}

	WeaponDef::~WeaponDef()
	{
	}

	ItemPtr WeaponDef::Create()
	{
		return ItemPtr(new Weapon(this));
	}

	void	WeaponDef::Parse(TiXmlElement* def)
	{
		ItemDef::Parse(def);
		AmmoTag = def->Attribute("AmmoTag");
	}

	Weapon::Weapon(WeaponDef* def) : Item(def)
	{
		SetSlot(Item::Weapon);
		mAmmoTag = def->AmmoTag;
	}

	Weapon::~Weapon()
	{
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
			ammo = FactoryManager::GetSingleton()->CreateItem(mAmmoTag);
			ammo->SetAmmo(0);
		}
		GetInventory()->Equip(ammo);
	}

	void	Weapon::OnUse(EntityPtr actor)
	{
		// Создаем снаряд
		EntityPtr bullet = FactoryManager::GetSingleton()->CreateEntity("Bullet", "");

		// Помещаем снаряд на слой
		actor->GetLevel()->GetLayer("Bullets")->Add(bullet);

		// Устанавливаем угол и координаты снаряда
		bullet->SetAngle(actor->GetAngle());
		bullet->SetPosition(actor->GetPosition().x, actor->GetPosition().y);

		// Настраиваем владельца снаряда
		(boost::shared_dynamic_cast<behaviour::Bullet, Behaviour>(bullet->GetBehaviour()))->SetGunslinger(actor->GetBehaviour());
	}

	void	Weapon::SetAmmoTag(std::string ammoTag)
	{
		mAmmoTag = ammoTag;
	}
};