#include "ZombieLand.h"
#include "ZombieLand/Action/Shild.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Shild::Shild()
	{
		mCost = 10.0f;
		SetDuration(10);
	}

	Shild::~Shild()
	{
	}

	bool Shild::DoneCondition()
	{
		return GetEntity()->As<behaviour::Creature>()->GetEnergy() <= 0.0f;
	}

	void Shild::OnUpdate(float elapsedTime)
	{
		//GetBehaviour()->SetEnergy(GetBehaviour()->GetEnergy() - mCost * elapsedTime);
	}

	void Shild::OnStart()
	{
		mOldResistance = GetEntity()->As<behaviour::Destroyable>()->GetResistance();
		mOldSpeed = GetEntity()->As<behaviour::Creature>()->GetMoveAction()->GetSpeed();
		GetEntity()->As<behaviour::Destroyable>()->SetResistance(1.0f);
		GetEntity()->As<behaviour::Creature>()->GetMoveAction()->SetSpeed(mOldSpeed * 0.8f);

		GraphicsPtr g = FactoryManager::GetSingleton()->CreateGraphics("Effects/Shild");
		GetEntity()->GetGraphics()->Attach("ShildEffect", g);
	}

	void Shild::OnDone()
	{
		GetEntity()->GetGraphics()->Remove("ShildEffect");
		GetEntity()->As<behaviour::Creature>()->SetResistance(mOldResistance);
		GetEntity()->As<behaviour::Creature>()->GetMoveAction()->SetSpeed(mOldSpeed);
	}
}