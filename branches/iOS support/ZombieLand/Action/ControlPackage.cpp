#include "ZombieLand.h"
#include "ControlPackage.h"
#include "Control.h"

ControlPackage::ControlPackage()
{
}

ControlPackage::~ControlPackage()
{
}

bool ControlPackage::IsApplicable(BehaviourPtr behaviour) const
{
	return true;
}

ActionPtr ControlPackage::CreateAction() const
{
	action::Control* a = new action::Control();
	return ActionPtr(a);
}

AIPackagePtr ControlPackageDef::CreatePackage()
{
	return AIPackagePtr(new ControlPackage());
}
