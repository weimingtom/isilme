#ifndef ZOMBIELAND_ACTIONS_SEEK_H
#define ZOMBIELAND_ACTIONS_SEEK_H

#include <Isilme.h>
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	/// Поиск предмета (статического объекта)
	class Seek : public SpecialAction<Creature>
	{
	};
};

#endif