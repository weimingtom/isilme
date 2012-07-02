#include "ZombieLand.h"
#include "AvoidPackage.h"
#include "Avoid.h"
#include "../Behaviour/Creature.h"

AvoidPackage::AvoidPackage()
{
}

AvoidPackage::~AvoidPackage()
{
}

ActionPtr AvoidPackage::CreateAction() const
{
	action::Avoid* a = new action::Avoid();
	return ActionPtr(a);
}

bool AvoidPackage::IsApplicable(BehaviourPtr b) const
{
	behaviour::CreaturePtr c = boost::shared_dynamic_cast<behaviour::Creature>(b);

	float brave = c->GetAttributeValue("Brave");
	int enemiesCount = c->GetEnemiesCount();
	return brave < enemiesCount;
}

AIPackagePtr AvoidPackageDef::CreatePackage()
{
	return AIPackagePtr(new AvoidPackage());
}
