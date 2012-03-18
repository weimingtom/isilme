#ifndef ISILME_CORE_BEHAVIOURWRAPPER_H
#define ISILME_CORE_BEHAVIOURWRAPPER_H

#include "Definitions.h"
#include "Core/Behaviour.h"

class BehaviourWrapper : public Behaviour, public luabind::wrap_base
{
public:
	virtual void OnUpdate(float elapsedTime);
	static void defaultThink(Behaviour* b, float elapseTime);
};
#endif