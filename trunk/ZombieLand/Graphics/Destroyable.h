#ifndef ZOMBIELAND_GRAPHICS_DESTROYABLE_H
#define ZOMBIELAND_GRAPHICS_DESTROYABLE_H

#include <Isilme.h>
#include <Engine/Graphics/SpecialGraphics.h>
#include <Engine/Graphics/StateGraphics.h>

#include "ZombieLand/Behaviour/Destroyable.h"

namespace graphics
{
	class Destroyable : public StateGraphics<behaviour::Destroyable>
	{
	};
};

#endif