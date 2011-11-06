#include "ZombieLand.h"
#include "AttackTarget.h"
#include "ZombieLand/Action/Attack.h"
#include "ZombieLand/Behaviour/Destroyable.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Action/Move.h"

namespace action
{
	AttackTarget::AttackTarget()
	{
	}

	AttackTarget::~AttackTarget()
	{
	}

	void	AttackTarget::SetTarget(behaviour::DestroyablePtr target)
	{
		mTarget = target;
	}

	behaviour::DestroyablePtr AttackTarget::GetTarget()
	{
		return mTarget;
	}

	void	AttackTarget::OnStart()
	{
		mCreature = GetEntity()->As<behaviour::Creature>();
		if (mCreature->GetTarget() == 0)
		{
			Stop();
			return;
		}

		mAction = mCreature->GetMoveAction();
		GetEntity()->GetBehaviour()->StartAction(mAction);

		float angle = GetEntity()->GetAngleTo(mCreature->GetTarget());
		mAction->SetAngle(angle);
		GetEntity()->SetAngle(angle);
	}

	void	AttackTarget::OnUpdate(float elapsedTime)
	{
		mCreature->SetTarget();
		if (mCreature->GetTarget() == 0)
		{
			Stop();
			return;
		}
		float angle = GetEntity()->GetAngleTo(mCreature->GetTarget());
		mAction->SetAngle(angle);
		GetEntity()->SetAngle(angle);

		if (GetEntity()->GetDistanceTo(mCreature->GetTarget()) < 1.2f)
		{
			ActionPtr attackAction = mCreature->GetAttackAction();
			if (!attackAction->IsActive())
			{
				mCreature->StartAction(attackAction);
			}
		}
	}

	void	AttackTarget::OnDone()
	{
		mAction->Stop();
	}

	void	AttackTarget::OnForceStop()
	{
		OnDone();
	}
};
