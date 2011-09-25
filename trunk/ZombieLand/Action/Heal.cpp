#include "ZombieLand.h"
#include "ZombieLand/Action/Heal.h"

namespace action
{
	Heal::Heal()
	{
		mSpeed = 20.0f;
		mCost = 40.0f;
		SetDuration(1.0f);
	}

	Heal::~Heal()
	{
	}

	float Heal::GetCost()
	{
		return mCost;
	}

	void	Heal::OnStart()
	{

	}

	void Heal::OnUpdate(float elapsedTime)
	{
		GetEntity()->As<behaviour::Creature>()->SetHealth(GetEntity()->As<behaviour::Creature>()->GetHealth() + mSpeed * elapsedTime);
	}
};