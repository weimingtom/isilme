#include "ZombieLand.h"
#include "ZombieLand/Action/Wind.h"
#include "Query.h"

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
		
		QueryPtr targets = GetLevel()->AABBQuery( v.x - mDistance, v.y - mDistance, v.x + mDistance, v.y + mDistance);
		
		for (int i = 0; i < targets->GetEntitiesCount(); ++i)
			if (targets->GetEntity(i) != GetEntity())
		{
			float l = targets->GetEntity(i)->GetDistanceTo(v);
			Vector2 d = targets->GetEntity(i)->GetPosition() - v;
			d.Normalize();
			d *= mForce / (l * l);
			if (targets->GetEntity(i)->GetBody()->GetType() == BodyDef::Box2DBody)
			{
				b2Body* b = ((Box2DBody*)targets->GetEntity(i)->GetBody())->GetBox2DBody();
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