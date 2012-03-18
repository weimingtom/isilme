#ifndef ZOMBIELAND_BEHAVIOUR_DESTROYABLE_H
#define ZOMBIELAND_BEHAVIOUR_DESTROYABLE_H

#include <Engine/Isilme.h>
#include "ZombieLand/Action/Die.h"
#include "Activator.h"

namespace behaviour
{
	class DestroyableDef
	{
	public:
		DestroyableDef();

		virtual void Parse(TiXmlElement* element);

		float	Health;
		float	MaxHealth;
		float	Resistance;
		std::string Blood;
	};

	/// @interface IDestroyable
	class IDestroyable
	{
	public:
		virtual ~IDestroyable() {};

		/// Gets health of the object
		virtual float	GetHealth() const = 0;

		/// Sets health of the object
		virtual void	SetHealth(float health) = 0;

		/// Gets maximum health for the object
		virtual float	GetMaxHealth() const = 0;

		/// Sets maximum health for the object
		virtual void	SetMaxHealth(float health) = 0;

		/// Gets resistance for the object
		virtual float	GetResistance() const = 0;

		/// Sets resistance
		virtual void	SetResistance(float resistance) = 0;

		/// Implements getting damage
		virtual void	Damage(float damage) = 0;

		/// Callback for die event
		virtual void OnDie() = 0;
	};

	/// @class Destroyable
	/// Simple destroyable implementation
	class Destroyable : public IDestroyable
	{
	public:
		Destroyable();
		virtual ~Destroyable();

		void Init(DestroyableDef* def);

		/// Возврашщает здоровье объекта
		virtual float	GetHealth() const;

		/// Установить здоровье
		virtual void	SetHealth(float health);

		/// Возвращает максимум здоровья
		virtual float	GetMaxHealth() const;

		/// Установить максимум здоровья
		virtual void	SetMaxHealth(float health);

		/// Возвращает сопротивляемость
		virtual float	GetResistance() const;

		/// Установить сопротивляемость
		virtual void	SetResistance(float resistance);

		/// Получить урон с учетом сопротивляемости
		virtual void	Damage(float damage);

		void	SetHitSound(std::string sound);
		
		void	SetBloodEntity(std::string blood);
	protected:
	private:
		float	mHealth;
		float	mMaxHealth;
		float	mResistance;

		HEFFECT mHitSound;
		std::string mBlood;
	};

};

#endif