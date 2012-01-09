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

ActionPtr WanderPackage::CreateAction()
{
	return ActionPtr(new action::Wander());
}

AIPackagePtr WanderPackageDef::CreatePackage()
{
	return AIPackagePtr(new WanderPackage());
}
