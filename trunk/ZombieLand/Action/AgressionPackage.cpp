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

ActionPtr AgressionPackage::CreateAction() const
{
	action::AttackTarget* a = new action::AttackTarget();
	a->SetDuration(2.0f);

	return ActionPtr(a);
}

bool AgressionPackage::IsApplicable(BehaviourPtr b) const
{
	return false;
	//behaviour::CreaturePtr c = GetEntity()->As<behaviour::Creature>();
	//c->SetTarget();
	//return c->GetTarget() != 0;
}

AIPackagePtr AgressionPackageDef::CreatePackage()
{
	return AIPackagePtr(new AgressionPackage());
}
