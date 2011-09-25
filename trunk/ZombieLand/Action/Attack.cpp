#include "ZombieLand.h"
#include <Isilme.h>
#include "Attack.h"
#include "ZombieLand/Behaviour/Destroyable.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Attack::Attack()
	{
		mSound = 0;
		mDistance = 1.0f;
		mWidth = 0.5f;
		SetDuration(1.0f);
		mDamage = 10;
	}

	Attack::~Attack()
	{
	}

	void	Attack::OnStart()
	{
		Vector2 v = GetActor()->GetPosition() + Vector2(mDistance * cos(GetActor()->GetAngle()), mDistance * sin(GetActor()->GetAngle()));

		//b2AABB aabb;
		//aabb.lowerBound.Set(v.x - mDistance / 2, v.y - mDistance /2);
		//aabb.upperBound.Set(v.x + mDistance / 2, v.y + mDistance /2);

		//GetLevel()->GetWorld()->QueryAABB(this, aabb);
		EntityList entities;
		GetLevel()->AABBQuery(&entities, v.x - mDistance / 2, v.y - mDistance /2,v.x + mDistance / 2, v.y + mDistance /2);
		for (EntityList::iterator it = entities.begin(); it != entities.end(); ++it)
			if (*it != GetActor())
			{
				behaviour::DestroyablePtr d = (*it)->As<behaviour::Destroyable>();
				if (d)
				{
					d->Damage(mDamage);
				}
			}
	}

	void	Attack::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}
};