#include "ZombieLand.h"
#include "Zombie.h"
#include "Destroyable.h"
#include "ZombieLand/LootTable.h"
#include "Engine/include/FactoryManager.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"

namespace behaviour
{
	DestroyableDef::DestroyableDef()
	{
		MaxHealth = 100.0f;
		Health = MaxHealth;
		Blood = "";
		Resistance = 0.0f;
		Loot = "";
	}

	BehaviourPtr DestroyableDef::Create()
	{
		return BehaviourPtr(new Destroyable(this));
	}

	void	DestroyableDef::Parse(TiXmlElement* element)
	{
		if (element == 0)
			return;

		/// Загружаем базовые характеристики
		element->QueryFloatAttribute("Health", &Health);
		element->QueryFloatAttribute("MaxHealth", &MaxHealth);
		element->QueryFloatAttribute("Resistance", &Resistance);

		///
		char* blood = const_cast<char*>(element->Attribute("Blood"));
		Blood = blood ? blood : "";

		/// Загружаем инвентарь
		TiXmlElement* inventoryElement = element->FirstChildElement("Inventory");
		ParseInventory(inventoryElement);

		/// Загружаем таблицу лута
		if (element->Attribute("Loot"))
			Loot = element->Attribute("Loot");
	}

	void	DestroyableDef::ParseInventory(TiXmlElement* inventoryELement)
	{
		if (!inventoryELement)
			return;

		TiXmlElement* itemElement = inventoryELement->FirstChildElement("Item");
		while (itemElement)
		{
			const char* tagAttr = itemElement->Attribute("Tag");
			if (tagAttr)
			{
				ItemInfo item;
				item.tag = tagAttr;
				item.ammo = 1;

				itemElement->QueryIntAttribute("Ammo", &item.ammo);
				int equip = 0;
				itemElement->QueryIntAttribute("Equip", &equip);
				item.equip = equip != 0;

				Items.push_back(item);
			}

			itemElement = itemElement->NextSiblingElement("Item");
		}
	}

	Destroyable::Destroyable(DestroyableDef* def)
	{
		mHitSound = 0;
		mMaxHealth = def->MaxHealth;
		mHealth = def->Health;
		mResistance = def->Resistance;
		mBlood = def->Blood;
		mLoot = def->Loot;

		mDieAction = action::DiePtr(new action::Die());

		/// Инвентарь
		mInventory = inventory::Inventory::New();
		for (std::list<ItemInfo>::iterator it = def->Items.begin(); it != def->Items.end(); ++it)
		{
			inventory::ItemPtr item = FactoryManager::GetSingleton()->CreateItem(it->tag);
			if (item)
			{
				item->SetAmmo(it->ammo);
				mInventory->AddItem(item);
				if (it->equip)
					mInventory->Equip(item);
			}
			else
			{
				
			}
		}
	}

	Destroyable::~Destroyable()
	{
	}
	
	inventory::InventoryPtr	Destroyable::GetInventory()
	{
		return mInventory;
	}

	LootTablePtr Destroyable::GetLootTable()
	{
		return LootManager::GetSingleton()->GetLootTable(mLoot);
	}

	float	Destroyable::GetHealth()
	{
		return mHealth;
	}

	float	Destroyable::GetMaxHealth()
	{
		return mMaxHealth;
	}

	float	Destroyable::GetResistance()
	{
		return mResistance;
	}

	void	Destroyable::SetHealth(float health)
	{
		mHealth = min(health, mMaxHealth);
	}

	void	Destroyable::SetMaxHealth(float health)
	{
		mMaxHealth = health;
	}

	void	Destroyable::SetResistance(float resistance)
	{
		mResistance = resistance;
	}

	void	Destroyable::Damage(float damage)
	{
		mHealth -= damage * (1.0f - mResistance);

		if (mHitSound)
		Engine::GetSingleton()->GetSoundSystem()->PlayEffect(mHitSound);

		if (mBlood != "")
		{
			EntityPtr blood = FactoryManager::GetSingleton()->CreateEntity(mBlood, "", GetLevel());
			blood->SetPosition(GetActor()->GetPosition().x, GetActor()->GetPosition().y);
			blood->SetAngle(GetActor()->GetAngle());
			GetLevel()->GetLayer("Grass")->Add(blood);
		}
	}

	void	Destroyable::Think(float elapsedTime)
	{
		if (mHealth <= 0.0f)
		{
			if (!mDieAction->IsActive())
				StartAction(mDieAction);
		}
	}

	action::DiePtr	Destroyable::GetDieAction()
	{
		return mDieAction;
	}

	void	Destroyable::SetHitSound(std::string sound)
	{
		mHitSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	void	Destroyable::SetBloodEntity(std::string blood)
	{
		mBlood = blood;
	}
};