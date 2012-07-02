#include "ZombieLand.h"
#include "WanderPackage.h"
#include "ZombieLand/Action/Wander.h"
#include "ZombieLand/Behaviour/Creature.h"

WanderPackage::WanderPackage()
{
}

WanderPackage::~WanderPackage()
{
}

ActionPtr WanderPackage::CreateAction() const
{
	return ActionPtr(new action::Wander());
}

bool WanderPackage::IsApplicable( BehaviourPtr behaviour ) const 
{
	return behaviour->GetActiveActionsCount() == 0;
}

AIPackagePtr WanderPackageDef::CreatePackage()
{
	return AIPackagePtr(new WanderPackage());
}
