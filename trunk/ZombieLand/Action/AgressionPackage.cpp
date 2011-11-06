#include "ZombieLand.h"
#include "AgressionPackage.h"
#include "ZombieLand/Action/AttackTarget.h"
#include "ZombieLand/Behaviour/Creature.h"

AgressionPackage::AgressionPackage()
{
}

AgressionPackage::~AgressionPackage()
{
}

ActionPtr AgressionPackage::CreateAction()
{
	action::AttackTarget* a = new action::AttackTarget();

	return ActionPtr(a);
}

bool AgressionPackage::CheckCondition(BehaviourPtr behaviour)
{
	return false;
}