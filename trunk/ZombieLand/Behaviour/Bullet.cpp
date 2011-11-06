#include "ZombieLand.h"
#include "Bullet.h"

namespace behaviour
{
	Bullet::Bullet(BulletDef* def) : Behaviour(def)
	{
		mSpeed = 10.0f;
		mDamage = 25.0f;
		isHit = false;
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Think(float elapsedTime)
	{
		if (mTarget != 0)
			mTarget->Damage(mDamage);

		if (isHit)
			GetActor()->Remove();

		GetActor()->GetBody()->SetLinearVelocity(Vector2(mSpeed * cos(GetActor()->GetAngle()), mSpeed * sin(GetActor()->GetAngle())));
	}

	void Bullet::HandleContact(b2Contact* contact, const b2Manifold* oldMainfold, Entity* other)
	{
		DestroyablePtr d;

		try
		{
			d = boost::shared_dynamic_cast<Destroyable, Behaviour>(other->GetBehaviour());
		}
		catch (...)
		{
		}

		if (d != 0 && d != mGunslinger)
		{
			mTarget = d;
		}

		if (d == mGunslinger)
			contact->SetEnabled(false);
		else
			isHit = true;
	}

	BehaviourPtr BulletDef::Create()
	{
		return BehaviourPtr(new Bullet(this));
	}

	void	Bullet::SetGunslinger(BehaviourPtr creature)
	{
		mGunslinger = creature;
	}
};