#ifndef AI_AGRESSION_PACKAGE_H
#define AI_AGRESSION_PACKAGE_H

#include <Isilme.h>
#include <Engine/include/AIPackage.h>
#include "ZombieLand/Include/Definitions.h"
#include "ZombieLand/Action/AttackTarget.h"
#include <Engine/Core/AIPackageDef.h>

/// Пакет ИИ, отвечающий за нападение на других агентов
class AgressionPackage : public AIPackage
{
public:
	AgressionPackage();
	virtual ~AgressionPackage();

	/// Проверяем, есть ли поблизости враждебно настроенные агенты
	virtual bool CheckCondition();

	/// Создает и настраивает действие атаки цели
	virtual ActionPtr CreateAction();
protected:
private:
};

class AgressionPackageDef : public AIPackageDef
{
	virtual AIPackagePtr CreatePackage();
};

#endif