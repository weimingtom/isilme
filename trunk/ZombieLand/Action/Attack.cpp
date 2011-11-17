#include "ZombieLand.h"
#include <Isilme.h>
#include "Attack.h"
#include "ZombieLand/Behaviour/Destroyable.h"
#include "ZombieLand/Behaviour/Creature.h"
#include "Query.h"

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
		QueryPtr entities = GetLevel()->AABBQuery( v.x - mDistance / 2, v.y - mDistance /2,v.x + mDistance / 2, v.y + mDistance /2);
		for (int i = 0; i < entities->GetEntitiesCount(); ++i)
			if (entities->GetEntity(i) != GetActor())
			{
				behaviour::DestroyablePtr d = entities->GetEntity(i)->As<behaviour::Destroyable>();
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