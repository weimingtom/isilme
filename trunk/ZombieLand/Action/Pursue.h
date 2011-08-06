#ifndef ZOMBIELAND_ACTIONS_PURSUE_H
#define ZOMBIELAND_ACTIONS_PURSUE_H

#include <Isilme.h>
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	/// Охота за оьбъектом
	class Pursue : public SpecialAction<Creature>
	{
	};
};

#endif