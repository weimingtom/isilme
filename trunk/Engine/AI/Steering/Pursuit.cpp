#include "IsilmePCH.h"
#include "Pursuit.h"
#include "ISteerable.h"

namespace steering
{

	Pursuit::Pursuit( VehiclePtr actor, VehiclePtr target ) : 
		mTarget(target),
		mActor(actor)
	{

	}

	Vector2 Pursuit::CalcVelocity()
	{
		Vector2 offset = mTarget->GetPosition()  - mActor->GetPosition();
		float distance = offset.Length();
		float timeInterval = std::min(0.1f, distance / mActor->GetMaxVelocity());
		Vector2 v = mTarget->PredictFuturePosition(timeInterval) - mActor->GetPosition();

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