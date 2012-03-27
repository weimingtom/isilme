#ifndef ISILME_AI_STEERING_LINEARWEIGHTSTEERING_H
#define ISILME_AI_STEERING_LINEARWEIGHTSTEERING_H

#include "ISteering.h"

namespace steering
{
	/// @class LinearWeightSteering
	class ISILME_API LinearWeightSteering : public ISteering
	{
	public:
		LinearWeightSteering(VehiclePtr actor);

		virtual Vector2 CalcVelocity() override;

		void AddSteering(SteeringPtr steering, float weight);
	private:
		typedef struct SteeringWeight
		{
			float weight;
			SteeringPtr steering;
		} SteeringWeight;

		typedef std::vector<SteeringWeight> SteeringList;

		/// Actor
		VehiclePtr mActor;

		/// All steerings
		SteeringList mSteeringData;
	};
}

#endif