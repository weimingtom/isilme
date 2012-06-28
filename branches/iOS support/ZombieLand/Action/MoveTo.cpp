#include "ZombieLand.h"
#include "MoveTo.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "Move.h"

namespace action
{
	MoveTo::MoveTo()
	{
	}

	MoveTo::~MoveTo()
	{
	}

	void	MoveTo::SetTarget(EntityPtr	entity)
	{
		mEntityTarget = entity;
	}

	void	MoveTo::SetTarget(Vector2 point)
	{
		mEntityTarget.reset();
		mPointTarget = point;
	}

	void	MoveTo::OnStart()
	{
		mCreature = GetEntity()->As<behaviour::Creature>();
		if (!mCreature)
			Stop();
		
		GetEntity()->GetBehaviour()->StartAction(mCreature->GetMoveAction());
	}

	void	MoveTo::OnDone()
	{
		mCreature->GetMoveAction()->Stop();
	}

	void	MoveTo::OnForceStop()
	{
		if (mCreature)
			OnDone();
	}

	void	MoveTo::OnUpdate(float elapsedTime)
	{
		Vector2 target;

		// Выбираем точку, к которой необходимо двигаться
		if (mEntityTarget)
		{
			target = mEntityTarget->GetPosition();
		}
		else
		{
			target = mPointTarget;
		}

		// Корректируем направление движения
		mCreature->GetMoveAction()->SetAngle(GetActor()->GetAngleTo(target));
	}
};