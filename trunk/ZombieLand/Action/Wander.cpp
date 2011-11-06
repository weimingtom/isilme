#include "ZombieLand.h"
#include "Wander.h"
#include "MoveTo.h"
#include "Move.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Wander::Wander()
	{
		SetDuration(1.0f);
	}

	Wander::~Wander()
	{
	}

	bool	Wander::DoneCondition()
	{
		return false;
	}

	void	Wander::OnStart()
	{
		mAction = GetEntity()->As<behaviour::Creature>()->GetMoveAction();
		GetEntity()->GetBehaviour()->StartAction(mAction);
		float angle = GetEntity()->GetAngle() + 1.57f;
		mAction->SetAngle(angle);
		GetEntity()->SetAngle(angle);
	}

	void	Wander::OnUpdate(float elapsedTime)
	{
	}

	void	Wander::OnDone()
	{
		mAction->Stop();
	}

	void	Wander::OnForceStop()
	{
	}
};