#include "ZombieLand.h"
#include "AgressionPackage.h"
#include "AttackTarget.h"
#include "../Behaviour/Creature.h"

AgressionPackage::AgressionPackage()
{
}

AgressionPackage::~AgressionPackage()
{
}

ActionPtr AgressionPackage::CreateAction() const
{
	action::AttackTarget* a = new action::AttackTarget();
	a->SetDuration(2.0f);

	return ActionPtr(a);
}

bool AgressionPackage::IsApplicable(BehaviourPtr b) const
{
	behaviour::CreaturePtr c = boost::shared_dynamic_cast<behaviour::Creature>(b);
	c->SetTarget();
	return c->GetTarget() != nullptr;
}

AIPackagePtr AgressionPackageDef::CreatePackage()
{
	return AIPackagePtr(new AgressionPackage());
}
