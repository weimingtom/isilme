#ifndef ZOMBIELAND_BEHAVIOUR_ZOMBIE_H
#define ZOMBIELAND_BEHAVIOUR_ZOMBIE_H

#include <Isilme.h>
#include "Creature.h"

namespace behaviour
{
	class ZombieDef : public CreatureDef
	{
	public:
		virtual BehaviourPtr Create();
	};

	class Zombie : public Creature
	{
	public:
		Zombie(ZombieDef* def);
		virtual ~Zombie();

		virtual void	Think(float elapsedTIme);

		static int GetZombieCount();

		virtual void SetActive(bool active);
	protected:
		static int mZombieCount;
	};

};

#endif