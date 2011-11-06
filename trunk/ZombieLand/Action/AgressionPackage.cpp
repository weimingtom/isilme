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
	a->SetDuration(2.0f);

	return ActionPtr(a);
}

bool AgressionPackage::CheckCondition(BehaviourPtr behaviour)
{
	behaviour::CreaturePtr c = boost::shared_dynamic_cast<behaviour::Creature>(behaviour);
	c->SetTarget();
	return c->GetTarget() != 0;
}