#include "IsilmePCH.h"
#include "Actuator.h"
#include "../Core/Action.h"

Actuator::Actuator( std::string id ) : 
	mID(id)
{

}

std::string Actuator::GetID() const
{
	return mID;
}

bool Actuator::IsLocked() const
{
	return mOwner != nullptr;
}

bool Actuator::LockByAction( ActionPtr action, bool force /*= false*/ )
{
	if (mOwner)
	{
		if (force)
		{
			mOwner->Stop();
			mOwner = action;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
