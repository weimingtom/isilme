#ifndef ISILME_AI_STEERING_OBSTACLEAVOIDANCE_H
#define ISILME_AI_STEERING_OBSTACLEAVOIDANCE_H

#include "SteeringTypes.h"
#include "ISteering.h"

namespace steering
{
	/// @class ObstacleAvoidance
	///
	/// Avoid obstacles
	/// Gets the nearest obstacle using the ray query in moving direction
	class ObstacleAvoidance : public ISteering
	{
	public:
		ObstacleAvoidance(VehiclePtr actor);

		virtual Vector2 CalcVelocity() override;

	protected:
		/// Calculate velocity vector to avoid concrete obstacle
		///
		/// @param obstacle		
		virtual Vector2	CalcVelocity(VehiclePtr obstacle);
	private:
		/// Actor
		VehiclePtr mActor;
	};
}
#endif