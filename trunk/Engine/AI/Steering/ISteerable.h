#ifndef ISILME_AI_STEERING_ISTEERABLE_H
#define ISILME_AI_STEERING_ISTEERABLE_H

#include "AITypes.h"

/// @interface ISteerable
/// Interface for object that can implement steering behaviour
class ISILME_API ISteerable
{
public:
	virtual ~ISteerable();

	/// Sets maximum acceleration
	virtual void SetMaxAcceleration(float maxAcceleration) = 0;

	/// Gets maximum acceleration
	virtual float GetMaxAcceleration() const = 0;

	/// Gets possible position in the future
	virtual Vector2 PredictFuturePosition(const float predictionTime) const = 0;
};

#endif