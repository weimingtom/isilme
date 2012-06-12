#include "ZombieLand.h"
#include "Wander.h"
#include "MoveTo.h"
#include "Move.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "../Behaviour/Activator.h"
#include "../Behaviour/Item.h"
#include "UseItem.h"

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
		behaviour::ActivatorPtr activator = behaviour::Activator::GetActivatorFor(GetEntity());

		behaviour::ItemPtr item = boost::shared_dynamic_cast<behaviour::Item>(activator);

		if (item != nullptr)
		{
			PickItem* a = new PickItem(item);
			GetEntity()->GetBehaviour()->StartAction(ActionPtr(a));
		}
	}

	void	Wander::OnDone()
	{
		mAction->Stop();
	}

	void	Wander::OnForceStop()
	{
	}
};