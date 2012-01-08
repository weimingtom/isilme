#include "IsilmePCH.h"
#include "AIPackageWrapper.h"

AIPackageWrapper::AIPackageWrapper()
{
}

AIPackageWrapper::~AIPackageWrapper()
{

}

bool AIPackageWrapper::CheckCondition( BehaviourPtr behaviour )
{
	bool result = luabind::call_member<bool, BehaviourPtr>(this, "CheckCondition", behaviour);
	return result;
}

ActionPtr AIPackageWrapper::CreateAction()
{
	ActionPtr result = luabind::call_member<ActionPtr>(this, "CreateAction");
	return result;
}

bool AIPackageWrapper::defaultCheckCondition(AIPackage* base, BehaviourPtr behaviour )
{
	return base->AIPackage::CheckCondition(behaviour);
}

ActionPtr AIPackageWrapper::defaultCreateAction(AIPackage* base)
{
	return base->AIPackage::CreateAction();
}
