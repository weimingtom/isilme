#ifndef ISILME_AI_STEERING_ISTEERING_H
#define ISILME_AI_STEERING_ISTEERING_H

#include "SteeringTypes.h"

/// 
class ISILME_API ISteering
{
public:
	virtual ~ISteering() {};

	/// Calculates desired velocity
	/// Use it for kinematic
	virtual Vector2 CalcVelocity() = 0;

	/// Calculates desired acceleration
	/// Use it for dynamic
	// virtual Vector2 CalcAcceleration() = 0;
};

#endif