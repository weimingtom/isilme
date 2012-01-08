#include "IsilmePCH.h"
#include "StateWrapper.h"


void StateWrapper::OnUpdate( float elapsedTime )
{
	luabind::call_member<void, float>(this, "OnUpdate", elapsedTime);
}

void StateWrapper::OnStart()
{
	luabind::call_member<void>(this, "OnStart");
}

void StateWrapper::OnResume()
{
	luabind::call_member<void>(this, "OnResume");
}

void StateWrapper::defaultOnUpdate( State* state, float elapsedTime )
{
	state->State::OnUpdate(elapsedTime);
}

void StateWrapper::defaultOnStart(State* state)
{
	state->State::OnStart();
}

void StateWrapper::defaultOnResume(State* state)
{
	state->State::OnResume();
}
