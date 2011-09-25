#ifndef ZOMBIELAND_ACTION_SHILD_H
#define ZOMBIELAND_ACTION_SHILD_H

#include <Isilme.h>
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
class Shild : public Action
{
	public:
		Shild();
		virtual ~Shild();

		virtual void OnStart();

		virtual void OnUpdate(float elapsedTIme);

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