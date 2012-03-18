#ifndef ISILME_CORE_STATEWRAPPER_H
#define ISILME_CORE_STATEWRAPPER_H

#include "Definitions.h"
#include "Core/State.h"

class ISILME_API StateWrapper : public State, public luabind::wrap_base
{
public:
	virtual void OnUpdate(float elapsedTime);
	virtual void OnStart();
	virtual void OnResume();

	static void defaultOnUpdate(State* state, float elapsedTime);
	static void defaultOnStart(State* state);
	static void defaultOnResume(State* state);
};
#endif