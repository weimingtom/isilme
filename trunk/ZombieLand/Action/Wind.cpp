#include "ZombieLand.h"
#include "ZombieLand/Action/Wind.h"

namespace action
{
	Wind::Wind()
	{
		mSound = 0;
		mDistance = 4.0f;
		SetDuration(0.3f);
		mDamage = 10;
		mForce = 100.0f;
		mCost = 20.0f;
	}

	Wind::~Wind()
	{
	}

	float	Wind::GetCost()
	{
		return mCost;
	}

	void	Wind::SetCost(float energy)
	{
		mCost = energy;
	}

	void	Wind::OnUpdate(float elapsedTime)
	{
		Vector2 v = GetActor()->GetPosition();
		
		EntityList targets;
		GetLevel()->AABBQuery(&targets, v.x - mDistance, v.y - mDistance, v.x + mDistance, v.y + mDistance);
		
		for (EntityList::iterator it = targets.begin(); it != targets.end(); ++it)
			if (*it != GetEntity())
		{
			float l = (*it)->GetDistanceTo(v);
			Vector2 d = (*it)->GetPosition() - v;
			d.Normalize();
			d *= mForce / (l * l);
			if ((*it)->GetBody()->GetType() == BodyDef::Box2DBody)
			{
				b2Body* b = ((Box2DBody*)(*it)->GetBody())->GetBox2DBody();
				b->ApplyLinearImpulse(d, b->GetPosition());
			}
		}
	}

	void	Wind::OnStart()
	{
		
	}

	void	Wind::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}
};