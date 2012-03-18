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
	LOG_D("Package was destroyed");
}

bool AIPackageWrapper::IsApplicable( BehaviourPtr behaviour ) const
{
	++callCounter;
	//self1 = luabind::detail::wrap_access::ref(*this);
	bool result = luabind::call_member<bool>(this, "CheckCondition");
	return result;
}

ActionPtr AIPackageWrapper::CreateAction() const
{
	ActionPtr result = luabind::call_member<ActionPtr>(this, "CreateAction");
	return result;
}

bool AIPackageWrapper::defaultIsApplciable( AIPackage* base, BehaviourPtr behaviour )
{
	return base->AIPackage::IsApplicable(behaviour);
}

ActionPtr AIPackageWrapper::defaultCreateAction(AIPackage* base)
{
	return base->AIPackage::CreateAction();
}
