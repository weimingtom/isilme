#include "ZombieLand.h"
#include "ControlPackage.h"
#include "Control.h"

ControlPackage::ControlPackage()
{
}

ControlPackage::~ControlPackage()
{
}

bool ControlPackage::CheckCondition()
{
	return true;
}

ActionPtr ControlPackage::CreateAction()
{
	action::Control* a = new action::Control();
	return ActionPtr(a);
}

AIPackagePtr ControlPackageDef::CreatePackage()
{
	return AIPackagePtr(new ControlPackage());
}
