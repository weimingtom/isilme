#include "IsilmePCH.h"
#include "Arrival.h"
#include "ISteerable.h"

namespace steering
{
	Arrival::Arrival( VehiclePtr actor, const Vector2& target, float slowDistance) : 
		mActor(actor),
		mTarget(target),
		mSlowDistance(slowDistance)
	{

	}

	Vector2 Arrival::CalcVelocity()
	{
		Vector2 targetOffset = mTarget - mActor->GetPosition();
		
		float distance = targetOffset.Length();
		float rampedSpeed = mActor->GetMaxVelocity() * (distance / mSlowDistance);
		float clippedSpeed = std::min(rampedSpeed, mActor->GetMaxVelocity());
		Vector2	desiredVelocity = (clippedSpeed / distance) * targetOffset;
		Vector2 steering = desiredVelocity - mActor->GetVelocity();

		// Limit
		steering.Normalize();
		steering = mActor->GetMaxVelocity() * steering;

		return steering;
	}

}