#ifndef ISILME_AI_STEERING_PRIORITYSTEERING_H
#define ISILME_AI_STEERING_PRIORITYSTEERING_H

#include "ISteering.h"

namespace steering
{
	class PrioritySteering : public ISteering	
	{
	public:
		PrioritySteering(VehiclePtr actor);

		virtual Vector2 CalcVelocity() override;
	private:
		typedef std::vector<SteeringPtr> SteeringList;

		SteeringList mSteeringData;
	};
}
#endif