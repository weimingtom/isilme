#include "IsilmePCH.h"
#include "AIPackage.h"

AIPackage::AIPackage()
{
}

AIPackage::~AIPackage()
{
}

ActionPtr	AIPackage::CreateAction()
{
	return ActionPtr();
}

bool AIPackage::CheckCondition()
{
	return true;
}


BehaviourPtr AIPackage::GetBehaviour()
{
	return mBehaviour.lock();
}

EntityPtr AIPackage::GetEntity()
{
	return mBehaviour.lock()->GetActor();
}
