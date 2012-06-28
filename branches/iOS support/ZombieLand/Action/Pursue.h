#ifndef ZOMBIELAND_ACTIONS_PURSUE_H
#define ZOMBIELAND_ACTIONS_PURSUE_H

#include "../Definitions.h"
#include "../Behaviour/Creature.h"

namespace action
{
	/// Охота за оьбъектом
	class Pursue : public SpecialAction<Creature>
	{
	};
};

#endif