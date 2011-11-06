#include "ZombieLand.h"
#include "ControlPackage.h"
#include "Control.h"

ControlPackage::ControlPackage()
{
}

ControlPackage::~ControlPackage()
{
}

bool ControlPackage::CheckCondition(BehaviourPtr behaviour)
{
	return true;
}

ActionPtr ControlPackage::CreateAction()
{
	action::Control* a = new action::Control();
	return ActionPtr(a);
}