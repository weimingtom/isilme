#include "IsilmePCH.h"
#include "AIPackage.h"
#include "Core/Action.h"
#include "Core/Behaviour.h"


bool AIPackage::IsApplicable( BehaviourPtr behaviour ) const
{
	return true;
}

ActionPtr AIPackage::CreateAction() const
{
	return ActionPtr();
}
