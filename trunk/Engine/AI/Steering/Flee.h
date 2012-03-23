#ifndef ISILME_AI_STEERING_FLEE_H
#define ISILME_AI_STEERING_FLEE_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class Flee
	///
	/// Flee
	/// desired_velocity = normalize (target - position) * max_speed; 
	/// steering = desired_velocity - velocity
	class Flee : public ISteering
	{
	public:
		Flee(VehiclePtr actor, const Vector2& target);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		/// Target
		Vector2 mTarget;
	};
}
#endif