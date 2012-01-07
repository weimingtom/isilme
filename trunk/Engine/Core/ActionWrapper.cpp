#include "IsilmePCH.h"
#include "ActionWrapper.h"

void ActionWrapper::OnStart()
{
	luabind::call_member<void>(this, "OnStart");
}

void ActionWrapper::OnDone()
{
	luabind::call_member<void>(this, "OnDone");
}

void ActionWrapper::OnUpdate( float elapsedTime )
{
	luabind::call_member<void, float>(this, "OnUpdate", elapsedTime);
}

void ActionWrapper::defaultOnStart( Action* base )
{
	base->Action::OnStart();
}

void ActionWrapper::defaultOnUpdate( Action* base, float elapsedTime )
{
	base->Action::OnUpdate(elapsedTime);
}

void ActionWrapper::defaultOnDone( Action* base )
{
	base->Action::OnDone();
}

void ActionWrapper::OnForceStop()
{
	luabind::call_member<void>(this, "OnForceStop");
}

void ActionWrapper::defaultOnForceStop( Action* base )
{
	base->Action::OnForceStop();
}
