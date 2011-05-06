#ifndef ZOMBIELAND_BEHAVIOUR_CREATURE_H
#define ZOMBIELAND_BEHAVIOUR_CREATURE_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"
#include "Destroyable.h"

namespace behaviour
{
	class CreatureDef : public DestroyableDef
	{
	public:
		virtual BehaviourPtr Create();

		virtual void Parse(TiXmlElement* element);

		float	Energy;
		float	MaxEnergy;
		float	EnergyRestoration;
	};

	class Creature : public Destroyable
	{
	public:
		Creature(CreatureDef* def);
		virtual ~Creature();

		action::MovePtr GetMoveAction();

		action::MovePtr GetMoveBackAction();

		action::ShotPtr GetShotAction();

		action::AttackPtr GetAttackAction();
		
		action::HealPtr	GetHealAction();

		action::WindPtr	GetWindAction();

		action::ShildPtr GetShildAction();

		virtual void	Think(float elapsedTIme);

		void	RotateToPoint(Vector2 position);

		void	SetEnergy(float energy);

		float	GetEnergy();

		void	SetMaxEnergy(float energy);

		float	GetMaxEnergy();
	protected:
		action::MovePtr	mMoveAction;
		action::MovePtr	mMoveBack;
		action::ShotPtr	mShotAction;
		action::AttackPtr mAttack;
		action::HealPtr mHealAction;
		action::WindPtr mWindAction;
		action::ShildPtr mShildAction;

		float	mEnergy;
		float	mMaxEnergy;
		float	mEnergyResoration;
	};

};
#endif