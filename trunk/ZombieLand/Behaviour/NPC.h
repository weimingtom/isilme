#ifndef ZOMBIELAND_BEHAVIOUR_NPC_H
#define ZOMBIELAND_BEHAVIOUR_NPC_H

#include <Isilme.h>
#include "Creature.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"
#include "ZombieLand/Item.h"

namespace behaviour
{
	class NPCDef : public CreatureDef
	{
	public:
		virtual BehaviourPtr Create();
	};

	class NPC : public Creature
	{
	public:
		NPC(NPC* def);
		virtual ~NPC();

		virtual void	Think(float elapsedTIme);

		/// Переключение оружия
		void	NextWeapon();

		/// Переключение способности
		void	NextSpell();

		/// Включить активатор
		void	SwitchActivator();

		/// Сохранить координаты игрока
		void	SavePoint();

		/// Оживить игрока
		void	Respawn();
	protected:

		EntityPtr	mTarget;

		void	SetTarget();
		void	ClearTarget();

		bool	isReloading;

		int		mCurrentWeapon;
		int		mCurrentSpell;
	
		Vector2	mCheckPoint;
	};
};
#endif