#include "IsilmePCH.h"
#include "AIPackage.h"

AIPackage::AIPackage()
{
}

AIPackage::~AIPackage()
{
}

void	AIPackage::Parse(TiXmlElement* element)
{
	TiXmlElement* targetElement = element->FirstChildElement("Target");
	TiXmlElement* conditionElement = element->FirstChildElement("Condition");
	TiXmlElement* scheduleElement = element->FirstChildElement("Schedule");
	TiXmlElement* flagsElement = element->FirstChildElement("Flags");

	if (flagsElement)
		ParseFlags(flagsElement);

	if (targetElement)
		ParseTarget(targetElement);

	if (conditionElement)
		ParseCondition(conditionElement);

	if (scheduleElement)
		ParseSchedule(scheduleElement);
}

void	AIPackage::ParseTarget(TiXmlElement* targetElement)
{
}

void	AIPackage::ParseCondition(TiXmlElement* condtitionElement)
{
}

void	AIPackage::ParseFlags(TiXmlElement* flagsElement)
{
}

void	AIPackage::ParseSchedule(TiXmlElement* scheduleElement)
{
}

ActionPtr	AIPackage::CreateAction()
{
	return ActionPtr();
}

bool AIPackage::CheckCondition(BehaviourPtr behaviour)
{
	if (mCondition)
	{
		return false;
	}
	else
	{
		return true;
	}
}

luabind::object AIPackage::GetCondition()
{
	return mCondition;
}