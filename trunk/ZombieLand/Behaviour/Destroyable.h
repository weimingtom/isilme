#ifndef ZOMBIELAND_BEHAVIOUR_DESTROYABLE_H
#define ZOMBIELAND_BEHAVIOUR_DESTROYABLE_H

#include <Isilme.h>
#include "ZombieLand/Action/Die.h"
#include "Activator.h"

namespace behaviour
{
	struct ItemInfo
	{
	public:
		std::string tag;
		int			ammo;
		bool		equip;
	};

	class DestroyableDef : public ActivatorDef
	{
	public:
		DestroyableDef();

		virtual BehaviourPtr Create();
		virtual void Parse(TiXmlElement* element);

		/// Чтение данных инвентаря
		void	ParseInventory(TiXmlElement* inventoryElement);

		float	Health;
		float	MaxHealth;
		float	Resistance;
		std::string Blood;
		std::string Loot;
		std::list<ItemInfo>	Items;
	};

	class Destroyable : public Activator
	{
	public:
		Destroyable(DestroyableDef* def);
		virtual ~Destroyable();

		/// Возврашщает здоровье объекта
		float	GetHealth();

		/// Установить здоровье
		void	SetHealth(float health);

		/// Возвращает максимум здоровья
		float	GetMaxHealth();

		/// Установить максимум здоровья
		void	SetMaxHealth(float health);

		/// Возвращает сопротивляемость
		float	GetResistance();

		/// Установить сопротивляемость
		void	SetResistance(float resistance);

		/// Получить урон с учетом сопротивляемости
		void	Damage(float damage);

		action::DiePtr	GetDieAction();

		virtual void	Think(float elapsedTime);

		void	SetHitSound(std::string sound);

		/// Возвращает снаряжение
		inventory::InventoryPtr	GetInventory();
		
		void	SetBloodEntity(std::string blood);

		/// Таблица выпадающих предметов 
		LootTablePtr GetLootTable();
	protected:
	private:
		float	mHealth;
		float	mMaxHealth;
		float	mResistance;

		action::DiePtr	mDieAction;
		HEFFECT mHitSound;
		std::string mBlood;
		std::string mLoot;
		inventory::InventoryPtr	mInventory;
	};

};

#endif