#ifndef ZOMBIELAND_ACTION_SHILD_H
#define ZOMBIELAND_ACTION_SHILD_H

#include <Isilme.h>
#include "Engine/Action/SpecialTactics.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
class Shild : public SpecialTactics<behaviour::Creature>
{
	public:
		Shild();
		virtual ~Shild();

		virtual void OnStart();

		virtual void OnThink(float elapsedTIme);

		virtual void OnDone();

		virtual bool	DoneCondition();

		void	SetSound(std::string sound);

		void	SetCost(float energy);

		float	GetCost();
	private:
		HEFFECT	mSound;
		float mCost;
		float mOldResistance;
		float mOldSpeed;
};

};

#endif