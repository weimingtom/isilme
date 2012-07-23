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

	void Bullet::OnUpdate(float elapsedTime)
	{
		if (mTarget != 0)
			mTarget->Damage(mDamage);

		if (isHit)
			GetActor()->Remove();

        Vector2 velocity(mSpeed * cos(GetActor()->GetAngle()), mSpeed * sin(GetActor()->GetAngle()));
		GetActor()->GetBody()->SetLinearVelocity(velocity);
	}

	void Bullet::HandleContact(b2Contact* contact, const b2Manifold* oldMainfold, Entity* other)
	{
		DestroyablePtr d;

		d = other->As<Destroyable>();

		if (d != nullptr && other->GetBehaviour() != mGunslinger)
		{
			mTarget = d;
		}

		if (other->GetBehaviour() == mGunslinger)
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