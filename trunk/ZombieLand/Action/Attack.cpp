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
		mDoingTime = 1.0f;
		mDamage = 10;
	}

	Attack::~Attack()
	{
	}

	void	Attack::OnStart()
	{
		Vector2 v = GetActor()->GetPosition() + Vector2(mDistance * cos(GetActor()->GetAngle()), mDistance * sin(GetActor()->GetAngle()));

		b2AABB aabb;
		aabb.lowerBound.Set(v.x - mDistance / 2, v.y - mDistance /2);
		aabb.upperBound.Set(v.x + mDistance / 2, v.y + mDistance /2);

		GetLevel()->GetWorld()->QueryAABB(this, aabb);
	}

	void	Attack::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	bool	Attack::ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		Entity* entity = (Entity*)(body->GetUserData());
		if (entity == GetActor().get())
			return true;

		try
		{
			behaviour::DestroyablePtr d = boost::shared_dynamic_cast<behaviour::Destroyable>( entity->GetBehaviour());

			if (d != 0)
				d->Damage(mDamage);
		}
		catch (...)
		{
		}

		return true;
	}
};