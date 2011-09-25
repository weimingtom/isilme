#ifndef ZOMBIELAND_ACTION_WIND_H
#define ZOMBIELAND_ACTION_WIND_H

#include <Isilme.h>
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
class Wind : public Action
{
	public:
		Wind();
		virtual ~Wind();

		virtual void OnStart();

		virtual void OnUpdate(float elapsedTIme);

		void	SetSound(std::string sound);
		
		void	SetCost(float energy);

		float	GetCost();
	private:
		HEFFECT	mSound;
		float mDamage;
		float mDistance;
		float mForce;
		float mCost;
};

};

#endif