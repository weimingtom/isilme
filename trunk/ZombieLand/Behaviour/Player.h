#ifndef ZOMBIELAND_BEHAVIOUR_PLAYER_H
#define ZOMBIELAND_BEHAVIOUR_PLAYER_H

#include <Isilme.h>
#include "Creature.h"
#include "ZombieLand/Action/Heal.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"

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

		action::WindPtr GetWindAction();
		action::ShildPtr GetShildAction();
		action::HealPtr GetHealAction();
	protected:
		action::WindPtr mWindAction;
		action::ShildPtr mShildAction;
		action::HealPtr mHealAction;

		EntityPtr	mTarget;

		void	SetTarget();
		void	ClearTarget();
	};

};
#endif