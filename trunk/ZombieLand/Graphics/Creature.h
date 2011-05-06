#ifndef ZOMBIELAND_GRAPHICS_CREATURE_H
#define ZOMBIELAND_GRAPHICS_CREATURE_H

#include <Isilme.h>
#include <Engine/Graphics/SpecialGraphics.h>
#include <Engine/Graphics/StateGraphics.h>
#include "ZombieLand/Behaviour/Creature.h"

namespace graphics
{
	class Creature : public StateGraphics<behaviour::Creature>
	{
	public:
		Creature(StateGraphicsDef<behaviour::Creature>* def)  :
			StateGraphics<behaviour::Creature>(def)
		{
			int a = 4;		
		}	

		virtual ~Creature() {}

		virtual void	SelectState();

		virtual void	Render(float x, float y, float angle);
	};

 	class CreatureDef : public StateGraphicsDef<behaviour::Creature>
	{
	public:
		GraphicsPtr	Create()
		{
			return GraphicsPtr(new Creature(this));
		}
	};
};

#endif