#include "IsilmePCH.h"
#include "LinearWeightSteering.h"
#include "ISteerable.h"

namespace steering
{
	LinearWeightSteering::LinearWeightSteering(VehiclePtr actor) :
		mActor(actor)
	{

	}

	Vector2 LinearWeightSteering::CalcVelocity()
	{
		Vector2 steering;

		for (SteeringList::iterator it = mSteeringData.begin(); it != mSteeringData.end(); ++it)
		{
			steering += it->weight * it->steering->CalcVelocity();
		}

		return steering;
	}

	void LinearWeightSteering::AddSteering( SteeringPtr steering, float weight )
	{
		SteeringWeight s;
		s.steering = steering;
		s.weight = weight;
		mSteeringData.push_back(s);
	}
}
