#include "IsilmePCH.h"
#include "Seek.h"
#include "ISteerable.h"

namespace steering
{
	Seek::Seek( VehiclePtr actor, const Vector2& target ) :
		mActor(actor),
		mTarget(target)
	{
	}

	Vector2 Seek::CalcVelocity()
	{
		Vector2 v = mTarget - mActor->GetPosition();

		if (v.LengthSquared() < 1E-6)
			return Vector2(0.0f, 0.0f);

		v.Normalize();
		v = mActor->GetMaxVelocity() * v;
		v -= mActor->GetVelocity();
		
		// Limit
		v.Normalize();
		v = mActor->GetMaxVelocity() * v;

		return v;
	}

}