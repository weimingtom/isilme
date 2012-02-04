#include "IsilmePCH.h"
#include "AIPackageWrapper.h"

static unsigned long long callCounter = 0;

AIPackageWrapper::AIPackageWrapper()
{
	int a = 4;
	self1 = luabind::detail::wrap_access::ref(*this);
	int b = 0;

	//luabind::gettable(state)
	//luabind::object table = luabind::newtable( luaState );

	//table[self1] = self1;

	//return table;
}

AIPackageWrapper::~AIPackageWrapper()
{
	LOG_W("Package was destroyed");
}

bool AIPackageWrapper::CheckCondition()
{
	++callCounter;
	self1 = luabind::detail::wrap_access::ref(*this);
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
