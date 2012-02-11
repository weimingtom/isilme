#ifndef ISILME_CORE_ACTIONWRAPPER_H
#define ISILME_CORE_ACTIONWRAPPER_H

#include "Definitions.h"
#include "Action.h"

class ISILME_API ActionWrapper : public Action, public luabind::wrap_base
{
public:
	virtual ~ActionWrapper();
	virtual void OnStart();
	virtual void OnDone();
	virtual void OnUpdate(float elapsedTime);
	virtual void OnForceStop();

	static void defaultOnStart(Action* base);
	static void defaultOnDone(Action* base);
	static void defaultOnUpdate(Action* base, float elapsedTime);
	static void defaultOnForceStop(Action* base);
};
#endif