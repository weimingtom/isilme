#include "ZombieLand.h"
#include "ZombieLand/Action/Move.h"
#include "ZombieLand/Behaviour/Creature.h"

namespace action
{
	Move::Move()
	{
		mSpeed = 0.0f;
		mSound = 0;
		mChannel = 0;
		mAngle = 0;
	}

	Move::~Move()
	{
	}

	void	Move::SetSound(std::string sound)
	{
		mSound = Engine::GetSingleton()->GetResourceManager()->GetEffect(sound);
	}

	void	Move::OnForceStop()
	{
		OnDone();
	}

	void	Move::SetAngle(float angle)
	{
		mAngle = angle;
	}

	void	Move::OnUpdate(float elapsedTime)
	{
		EntityPtr e = GetEntity();
		float da = 0.0f;
		float ds = 1.0f;

		Vector2 v(cos(mAngle) * mSpeed * ds , sin(mAngle) * mSpeed * ds);

		b2Body* body = ((Box2DBody*)e->GetBody())->GetBox2DBody();

		//body->SetLinearVelocity(v);

		v.x *= body->GetMass() * 10;
		v.y *= body->GetMass() * 10;
		body->ApplyForce(v, e->GetPosition());

		Vector2 cv = body->GetLinearVelocity();
		float fv = abs(cv.Length());
		if (fv > abs(mSpeed) && fv > 0.00001)
		{
			cv.x *= abs(mSpeed) / fv;
			cv.y *= abs(mSpeed) / fv;
			body->SetLinearVelocity(cv);
		}
	}

	void	Move::OnStart()
	{
		if (mSound)
			mChannel = Engine::GetSingleton()->GetSoundSystem()->PlayEffect(mSound, true);

		mSpeed =  GetEntity()->As<behaviour::Creature>()->GetAttribute("Speed");
	}

	void	Move::OnDone()
	{
		if (mChannel)
			Engine::GetSingleton()->GetSoundSystem()->StopChannel(mChannel);

		EntityPtr e = GetEntity();
		Vector2 v(0.0f, 0.0f);

		if (e != 0)
			e->GetBody()->SetLinearVelocity(v);
	}
};