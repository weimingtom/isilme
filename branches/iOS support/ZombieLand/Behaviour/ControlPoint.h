#ifndef ZOMBIELAND_BEHAVIOUR_CONTROLPOINT_H
#define ZOMBIELAND_BEHAVIOUR_CONTROLPOINT_H

#include "Definitions.h"

namespace behaviour
{
	/// @class ControlPoint
	/// Behavior model for control points
	class ControlPoint : public Behaviour
	{
	public:
		ControlPoint();
		virtual ~ControlPoint();

		virtual void OnUpdate(float elapsedTime) override;
	private:
		// Fraction, that own the point
		FractionPtr mOwner;

		// complete status in [0;100]
		float mCompleteStatus;
	};

	class ControlPointDef : public BehaviourDefinition
	{
	public:
	};
}

#endif