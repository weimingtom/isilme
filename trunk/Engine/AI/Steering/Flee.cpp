#include "IsilmePCH.h"
#include "Flee.h"
#include "ISteerable.h"

namespace steering
{
	Flee::Flee( VehiclePtr actor, const Vector2& target ) : 
		mActor(actor),
		mTarget(target)
	{

	}

	Vector2 Flee::CalcVelocity()
	{
		Vector2 v = mActor->GetPosition() - mTarget;
		v.Normalize();
		v = mActor->GetMaxVelocity() * v;
		v -= mActor->GetVelocity();

		return v;
	}

}