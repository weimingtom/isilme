#include "ZombieLand.h"
#include "AvoidPackage.h"
#include "Avoid.h"
#include "ZombieLand/Behaviour/Creature.h"

AvoidPackage::AvoidPackage()
{
}

AvoidPackage::~AvoidPackage()
{
}

ActionPtr AvoidPackage::CreateAction()
{
	action::Avoid* a = new action::Avoid();
	return ActionPtr(a);
}

bool AvoidPackage::CheckCondition()
{
	behaviour::CreaturePtr c = GetEntity()->As<behaviour::Creature>();

	float brave = c->GetAttributeValue("Brave");
	int enemiesCount = c->GetEnemiesCount();
	return brave < enemiesCount;
}

AIPackagePtr AvoidPackageDef::CreatePackage()
{
	return AIPackagePtr(new AvoidPackage());
}
