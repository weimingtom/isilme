#ifndef ZOMBIELAND_ACTIONS_SEEK_H
#define ZOMBIELAND_ACTIONS_SEEK_H

#include "../Definitions.h"
#include "../Behaviour/Creature.h"

namespace action
{
	/// Поиск предмета (статического объекта)
	class Seek : public SpecialAction<Creature>
	{
	};
};

#endif