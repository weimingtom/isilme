#include "ZombieLand.h"
#include "ZombieLand/Graphics/Creature.h"
#include "ZombieLand/Action/Attack.h"
#include "ZombieLand/Action/Move.h"

namespace graphics
{
	void	Creature::SelectState()
	{
		if (GetBehaviour()->GetDieAction()->IsActive())
		{
			SetState("Die");
		}
		else if (GetBehaviour()->GetAttackAction()->IsActive())
		{
			SetState("Attack");
		}
		else if (GetBehaviour()->GetShotAction()->IsActive())
		{
			SetState("Shot");
		}
		else if (GetBehaviour()->GetMoveAction()->IsActive())
		{
			SetState("Move");
		}
		else if (GetBehaviour()->GetMoveBackAction()->IsActive())
		{
			SetState("MoveBack");
		}
		else if (GetBehaviour()->IsActive())
		{
			SetState("Idle");
		}
	}

	void	Creature::Render(float x, float y, float angle)
	{
		StateGraphics<behaviour::Creature>::Render(x, y, angle);
	}
}