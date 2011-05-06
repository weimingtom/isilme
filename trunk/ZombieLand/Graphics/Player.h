#ifndef ZOMBIELAND_GRAPHICS_PLAYER_H
#define ZOMBIELAND_GRAPHICS_PLAYER_H

#include <Isilme.h>
#include <Engine/Graphics/SpecialGraphics.h>
#include <Engine/Graphics/StateGraphics.h>
#include "ZombieLand/Graphics/Creature.h"
#include "ZombieLand/Behaviour/Player.h"

namespace graphics
{

	class Player : public StateGraphics<behaviour::Player>
	{
	public:
		Player(StateGraphicsDef<behaviour::Player>* def)  :
			 StateGraphics<behaviour::Player>(def)
		{
			int a = 4;		
		}	

		virtual ~Player() {}

		virtual void	SelectState();

		virtual void Render(float x, float y, float angle);
	};
	
 	class PlayerDef : public  StateGraphicsDef<behaviour::Player>
	{
	public:
		GraphicsPtr	Create()
		{
			return GraphicsPtr(new Player(this));
		}
	};
};

#endif