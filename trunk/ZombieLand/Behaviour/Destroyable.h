#ifndef ZOMBIELAND_BEHAVIOUR_DESTROYABLE_H
#define ZOMBIELAND_BEHAVIOUR_DESTROYABLE_H

#include <Isilme.h>
#include "ZombieLand/Action/Die.h"
#include "Activator.h"

namespace behaviour
{
	class DestroyableDef : public BehaviourDefinition
	{
	public:
		DestroyableDef();

		virtual BehaviourPtr Create();
		virtual void Parse(TiXmlElement* element);

		float	Health;
		float	MaxHealth;
		float	Resistance;
		std::string Blood;
		std::string Loot;
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

		void	SetBloodEntity(std::string blood);

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
	};

};

#endif