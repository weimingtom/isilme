#ifndef ZOMBIELAND_ACTIONS_KEEP_HEALTH_H
#define ZOMBIELAND_ACTIONS_KEEP_HEALTH_H

#include "Definitions.h"

namespace action
{
	/// Тактика сохранения здоровья
	/// Если запас здоровья меньше указанного минимума - использовать аптечку
	class KeepHealthPackage : public AIPackage
	{
	public:
		KeepHealthPackage();
		virtual ~KeepHealthPackage();

		virtual ActionPtr CreateAction();

		virtual bool CheckCondition(BehaviourPtr behaviour);
	private:
	};
}

#endif