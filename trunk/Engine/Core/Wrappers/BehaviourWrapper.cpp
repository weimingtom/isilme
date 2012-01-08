#include "IsilmePCH.h"
#include "BehaviourWrapper.h"

void BehaviourWrapper::Think( float elapsedTime )
{
	luabind::call_member<void, float>(this, "Think", elapsedTime);
}

void BehaviourWrapper::defaultThink( Behaviour* b, float elapseTime )
{
	b->Behaviour::Think(elapseTime);
}
