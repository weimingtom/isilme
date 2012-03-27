#ifndef ISILME_AI_STEERING_ISTEERABLE_H
#define ISILME_AI_STEERING_ISTEERABLE_H

#include "SteeringTypes.h"

/// @interface ISteerable
/// Interface for object that can implement steering behaviour
class ISILME_API IVehicle
{
public:
	virtual ~IVehicle() {};

	/// Sets maximum acceleration
	virtual void SetMaxAcceleration(float maxAcceleration) = 0;

	/// Gets maximum acceleration
	virtual float GetMaxAcceleration() const = 0;

	/// Gets possible position in the future
	virtual Vector2 PredictFuturePosition(const float predictionTime) const = 0;

	/// Gets current position
	virtual Vector2 GetPosition() const = 0;

	/// Gets maximum velocity
	virtual float GetMaxVelocity() const = 0;

	/// Gets current velocity
	virtual Vector2 GetVelocity() const = 0;

	/// Gets nearest object in direction
	///
	/// @param		direction vector
	/// @param		maxDistance vector length
	virtual VehiclePtr	RayQuery(const Vector2 direction, float maxDistance) = 0;
};

#endif