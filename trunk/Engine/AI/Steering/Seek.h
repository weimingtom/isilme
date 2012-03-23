#ifndef ISILME_AI_STEERING_SEEK_H
#define ISILME_AI_STEERING_SEEK_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class Seek
	///
	/// Seeking 
	/// desired_velocity = normalize (position - target) * max_speed; 
	/// steering = desired_velocity - velocity
	class Seek : public ISteering
	{
	public:
		Seek(VehiclePtr actor, const Vector2& target);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		/// Target
		Vector2 mTarget;
	};
}
#endif