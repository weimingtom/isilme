#include "IsilmePCH.h"
#include "Wander.h"
#include "ISteerable.h"

namespace steering
{
	Wander::Wander( VehiclePtr actor ) :
		mActor(actor),
		mTimes(0)
	{

	}

	Vector2 Wander::CalcVelocity()
	{
		return Vector2(0.0f, 0.0f);
	}

}