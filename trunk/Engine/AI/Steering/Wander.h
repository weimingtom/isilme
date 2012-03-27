#ifndef ISILME_AI_STEERING_WANDER_H
#define ISILME_AI_STEERING_WANDER_H

#include "ISteering.h"

namespace steering
{
	class Wander : public ISteering
	{
	public:
		Wander(VehiclePtr actor);

		virtual Vector2 CalcVelocity() override;
	private:
		/// Actor
		VehiclePtr mActor;

		///
		int			mTimes;
	};
}
#endif