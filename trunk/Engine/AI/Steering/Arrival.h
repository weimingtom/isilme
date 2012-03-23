#ifndef ISILME_AI_STEERING_ARRIVAL_H
#define ISILME_AI_STEERING_ARRIVAL_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class Arrival
	///
	/// Arrive to point 
	// target_offset = target - position
	// distance = length (target_offset)
	// ramped_speed = max_speed * (distance / slowing_distance)
	// clipped_speed = minimum (ramped_speed, max_speed)
	// desired_velocity = (clipped_speed / distance) * target_offset
	// steering = desired_velocity - velocity
	class Arrival : public ISteering
	{
	public:
		Arrival(VehiclePtr actor, const Vector2& target, float slowDistance);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		/// Target
		Vector2 mTarget;

		/// Distance when to slow down
		float mSlowDistance;
	};
}
#endif