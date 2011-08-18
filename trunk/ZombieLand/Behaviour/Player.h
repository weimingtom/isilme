#ifndef ZOMBIELAND_BEHAVIOUR_PLAYER_H
#define ZOMBIELAND_BEHAVIOUR_PLAYER_H

#include <Isilme.h>
#include "Creature.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"
#include "Engine/Inventory/Item.h"

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

		/// ������������ ������
		void	NextWeapon();

		/// ������������ �����������
		void	NextSpell();

		/// �������� ���������
		void	SwitchActivator();

		/// ��������� ���������� ������
		void	SavePoint();

		/// ������� ������
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