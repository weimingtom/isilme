#ifndef ISILME_AI_STEERING_EVASION_H
#define ISILME_AI_STEERING_EVASION_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class Evasion
	///
	/// Evasion
	/// predicted target = target + 
	/// desired_velocity = normalize (predicted_target - position) * max_speed; 
	/// steering = desired_velocity - velocity
	class Evasion : public ISteering
	{
	public:
		Evasion(VehiclePtr actor, VehiclePtr target);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		/// Target
		VehiclePtr mTarget;
	};
}
#endif