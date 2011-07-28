#ifndef ZOMBIELAND_BEHAVIOUR_PLAYER_H
#define ZOMBIELAND_BEHAVIOUR_PLAYER_H

#include <Isilme.h>
#include "Creature.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"
#include "ZombieLand/Item.h"

namespace behaviour
{
	class PlayerDef : public CreatureDef
	{
	public:
		virtual BehaviourPtr Create();
	};

	class Player : public Creature
	{
	public:
		Player(PlayerDef* def);
		virtual ~Player();

		virtual void	Think(float elapsedTIme);

		/// Переключение оружия
		void	NextWeapon();

		/// Переключение способности
		void	NextSpell();

		/// Включить активатор
		void	SwitchActivator();
	protected:

		EntityPtr	mTarget;

		void	SetTarget();
		void	ClearTarget();

		bool	isReloading;

		int		mCurrentWeapon;
		int		mCurrentSpell;
	
	};
};
#endif