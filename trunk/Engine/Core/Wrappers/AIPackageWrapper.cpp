#include "IsilmePCH.h"
#include "AIPackageWrapper.h"

bool AIPackageWrapper::CheckCondition()
{
	bool result = luabind::call_member<bool>(this, "CheckCondition");
	return result;
}

ActionPtr AIPackageWrapper::CreateAction()
{
	ActionPtr result = luabind::call_member<ActionPtr>(this, "CreateAction");
	return result;
}

bool AIPackageWrapper::defaultCheckCondition(AIPackage* base)
{
	return base->AIPackage::CheckCondition();
}

ActionPtr AIPackageWrapper::defaultCreateAction(AIPackage* base)
{
	return base->AIPackage::CreateAction();
}
