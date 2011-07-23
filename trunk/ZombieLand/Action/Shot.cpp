#include "ZombieLand.h"
#include "Shot.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "ZombieLand/Behaviour/Bullet.h"
#include "ZombieLand/Items/Weapon.h"

namespace action
{
	Shot::Shot()
	{
		mEndingTime = 0.2f;
		mSound = 0;
	}

	Shot::~Shot()
	{
	}

	void	Shot::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	void	Shot::OnStart()
	{
		ItemPtr weapon = GetBehaviour()->GetInventory()->GetSlot(Item::Weapon);
		weapon->OnUse(GetActor());
	}
};