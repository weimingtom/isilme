#include "ZombieLand.h"
#include "Avoid.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Avoid::Avoid()
	{
		SetDuration(1.0f);
	}

	Avoid::~Avoid()
	{
	}

	void Avoid::OnStart()
	{
		mCreature = GetEntity()->As<behaviour::Creature>();
		mAction = mCreature->GetMoveAction();
		mAction->SetAngle(GetEntity()->GetAngle());
		GetEntity()->GetBehaviour()->StartAction(mAction);
	}

	void Avoid::OnDone()
	{
		mAction->Stop();
	}

	void Avoid::OnUpdate(float elapsedTime)
	{
		int n = mCreature->GetEnemiesCount();
		Vector2 p = GetEntity()->GetPosition();
		Vector2 v(0.0f, 0.0f);
		for (int i = 0; i < n; ++i)
		{
			Vector2 d = p - mCreature->GetEnemy(i)->GetActor()->GetPosition();
			v += d;
		}

		v = p + v;
		
		float angle = GetEntity()->GetAngleTo(v);
		if (!(angle >= -16.28 && angle < 16.28))
			return;
		mAction->SetAngle(angle);
		GetEntity()->SetAngle(angle);
		

		//if (mCreature->GetEnemiesCount() > 0)
		//{
		//	float angle = GetEntity()->GetAngleTo(mCreature->GetEnemy(0)->GetActor()) + 1.57f;
		//	if (!(angle >= -6.28 && angle < 6.28))
		//		return;
		//	mAction->SetAngle(angle);
		//	GetEntity()->SetAngle(angle);
		//}
	}

	void Avoid::OnForceStop()
	{
		OnDone();
	}
};