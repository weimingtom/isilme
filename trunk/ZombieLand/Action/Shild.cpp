#include "ZombieLand.h"
#include "ZombieLand/Action/Shild.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Shild::Shild()
	{
		mCost = 10.0f;
	}

	Shild::~Shild()
	{
	}

	bool Shild::DoneCondition()
	{
		return GetBehaviour()->GetEnergy() <= 0.0f;
	}

	void Shild::OnThink(float elapsedTime)
	{
		GetBehaviour()->SetEnergy(GetBehaviour()->GetEnergy() - mCost * elapsedTime);
	}

	void Shild::OnStart()
	{
		mOldResistance = GetBehaviour()->GetResistance();
		mOldSpeed = GetBehaviour()->GetMoveAction()->GetSpeed();
		GetBehaviour()->SetResistance(1.0f);
		GetBehaviour()->GetMoveAction()->SetSpeed(mOldSpeed * 0.8f);
	}

	void Shild::OnDone()
	{
		GetBehaviour()->SetResistance(mOldResistance);
		GetBehaviour()->GetMoveAction()->SetSpeed(mOldSpeed);
	}
}