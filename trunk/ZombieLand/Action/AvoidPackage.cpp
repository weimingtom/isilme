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

bool AvoidPackage::CheckCondition(BehaviourPtr b)
{
	behaviour::CreaturePtr c = boost::shared_dynamic_cast<behaviour::Creature>(b);

	float brave = c->GetAttribute("Brave");
	int enemiesCount = c->GetEnemiesCount();
	return brave < enemiesCount;
}