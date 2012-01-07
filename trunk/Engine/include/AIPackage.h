#ifndef ISILME_AIPACKAGE_H
#define ISILME_AIPACKAGE_H

#include "Definitions.h"
#include <luabind/luabind.hpp>

class ISILME_API AIPackage
{
public:
	AIPackage();
	virtual ~AIPackage();

	virtual void	Parse(TiXmlElement* element);
	virtual void	ParseCondition(TiXmlElement* conditionElement);
	virtual void	ParseFlags(TiXmlElement* flagsElement);
	virtual void	ParseTarget(TiXmlElement* targetElement);
	virtual void	ParseSchedule(TiXmlElement* scheduleElement);

	/// Создает тактическое действие для агента
	virtual ActionPtr	CreateAction();
	
	/// Условие выполнения пакета
	luabind::object	GetCondition();

	/// Проверяет выполняется ли условие для агента
	virtual bool CheckCondition(BehaviourPtr behaviour);
private:
	luabind::object mCondition;
};

#endif