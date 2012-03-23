#ifndef ISILME_AI_STEERING_PURSUIT_H
#define ISILME_AI_STEERING_PURSUIT_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class Pursuit
	///
	/// Pursuit 
	/// predicted_target = 
	/// desired_velocity = normalize (position - predicted_target) * max_speed; 
	/// steering = desired_velocity - velocity
	class Pursuit : public ISteering
	{
	public:
		Pursuit(VehiclePtr actor, VehiclePtr target);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		/// Target
		VehiclePtr mTarget;
	};
}
#endif