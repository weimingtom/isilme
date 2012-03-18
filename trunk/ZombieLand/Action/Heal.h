#ifndef ZOMBIELAND_ACTION_HEAL_H
#define ZOMBIELAND_ACTION_HEAL_H

#include "../Behaviour/Creature.h"

namespace action
{
	class Heal : public Action
	{
	public: 
		Heal();
		virtual ~Heal();

		virtual void OnUpdate(float elapsedTime);

		virtual void OnStart();

		float	GetSpeed();

		void	SetSpeed(float HPPerSecond);

		float	GetCost();

		void	SetCost(float energy);
	private:
		float mSpeed;
		float mCost;
	};
};

#endif