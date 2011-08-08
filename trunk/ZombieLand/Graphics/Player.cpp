#include "ZombieLand.h"
#include "ZombieLand/Graphics/Player.h"
#include "ZombieLand/Action/Wind.h"
#include "ZombieLand/Action/Shild.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Attack.h"

namespace graphics
{

void	Player::SelectState()
{
	if (GetBehaviour()->GetDieAction()->IsActive() || !GetBehaviour()->IsActive())
	{
		SetState("Die");
	}
	else if (GetBehaviour()->GetAttackAction()->IsActive())
	{
		SetState("Attack");
	}
	else if (GetBehaviour()->GetReloadAction()->IsActive())
	{
		SetState("Reload");
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
		GetState("Die")->Reset();
		SetState("Idle");
	}
}

void Player::Render(float x, float y, float angle)
{
		StateGraphics<behaviour::Player>::Render(x, y, angle);
}
};