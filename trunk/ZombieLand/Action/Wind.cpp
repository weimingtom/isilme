#include "ZombieLand.h"
#include "ZombieLand/Action/Wind.h"

namespace action
{
	Wind::Wind()
	{
		mSound = 0;
		mDistance = 4.0f;
		mDoingTime = 0.3f;
		mEndingTime = 1.0f;
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

	void	Wind::UpdateOnDoing(float elapsedTime)
	{
		Vector2 v = GetActor()->GetPosition();

		b2AABB aabb;
		aabb.lowerBound.Set(v.x - mDistance, v.y - mDistance);
		aabb.upperBound.Set(v.x + mDistance, v.y + mDistance);

		GetLevel()->GetWorld()->QueryAABB(this, aabb);
	}

	void	Wind::OnStart()
	{
		GetBehaviour()->SetEnergy(GetBehaviour()->GetEnergy() - mCost);
		Vector2 v = GetActor()->GetPosition();

		b2AABB aabb;
		aabb.lowerBound.Set(v.x - mDistance, v.y - mDistance);
		aabb.upperBound.Set(v.x + mDistance, v.y + mDistance);

		GetLevel()->GetWorld()->QueryAABB(this, aabb);
	}

	void	Wind::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	bool	Wind::ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();

		Vector2 p = body->GetPosition();
		Vector2 d = p - GetActor()->GetPosition();

		if (d.LengthSquared() < 1E-8)
			return true;

		float force = mForce / d.LengthSquared();
		d.Normalize();
		d *= force;

		body->ApplyLinearImpulse(d, body->GetPosition());

		return true;
	}
};