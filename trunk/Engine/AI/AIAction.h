#ifndef ISILME_AI_AIACTION_H
#define ISILME_AI_AIACTION_H

#include "Definitions.h"
#include "Action.h"

/// @class
/// Action adds
class AIAction : public Action
{
public:
	virtual ~AIAction();

	void LockActuator(std::string actuatorID);

	void LockActuator(ActuatorPtr actuator);
};
#endif