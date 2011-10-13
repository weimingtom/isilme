#include "ZombieLand.h"
#include "AttackTarget.h"
#include "ZombieLand/Action/Attack.h"
#include "ZombieLand/Behaviour/Destroyable.h"
#include "ZombieLand/Behaviour/Creature.h"

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
	}

	void	AttackTarget::OnUpdate(float elapsedTime)
	{
		behaviour::CreaturePtr creature = GetEntity()->As<behaviour::Creature>();

		if (!creature->GetShotAction()->IsActive())
		{
		}
		else if (!creature->GetAttackAction()->IsActive())
		{
		}
	}

	void	AttackTarget::OnDone()
	{
	}

	void	AttackTarget::OnForceStop()
	{
		OnDone();
	}
};
