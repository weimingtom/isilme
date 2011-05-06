#include "ZombieLand.h"
#include "ZombieLand/Action/Heal.h"

namespace action
{
	Heal::Heal()
	{
		mSpeed = 20.0f;
		mCost = 40.0f;
		mDoingTime = 1.0f;
		mEndingTime = 0.5f;
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
		GetBehaviour()->SetEnergy(GetBehaviour()->GetEnergy() - mCost);
	}

	void Heal::UpdateOnDoing(float elapsedTime)
	{
		GetBehaviour()->SetHealth(GetBehaviour()->GetHealth() + mSpeed * elapsedTime);
	}
};