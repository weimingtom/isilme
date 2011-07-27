#include "ZombieLand.h"
#include "Zombie.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Action/Attack.h"

namespace behaviour
{
	int Zombie::mZombieCount = 0;

	int Zombie::GetZombieCount()
	{
		return mZombieCount;
	}

	Zombie::Zombie(ZombieDef* def) : Creature(def)
	{
		SetUsable(false);
		mMoveAction->SetSpeed(1.5f);
		GetDieAction()->SetSound("../Data/Sounds/Zombie/Die.wav");

		SetHitSound("../Data/Sounds/Zombie/Hit.wav");
		mZombieCount++;
	}

	void	Zombie::SetActive(bool active)
	{
		Creature::SetActive(active);
		mZombieCount--;
	}

	Zombie::~Zombie()
	{
	}

	void	Zombie::Think(float elapsedTime)
	{
		Creature::Think(elapsedTime);

		EntityPtr player = FactoryManager::GetSingleton()->GetEntity("Player");

		Vector2 p = player->GetPosition();

		if ((p - GetActor()->GetPosition()).Length() > 6.0f)
		{
			if (GetMoveAction()->IsActive())
				GetMoveAction()->Stop();
			return;
		}
		if ((p - GetActor()->GetPosition()).Length() < 1.5f)
		{
			if (!(GetAttackAction()->IsActive()))
				StartAction(GetAttackAction());
		}

		RotateToPoint(p);

		if (!GetMoveAction()->IsActive())
			StartAction(GetMoveAction());
	}

	BehaviourPtr ZombieDef::Create()
	{
		return BehaviourPtr(new Zombie(this));
	}
};