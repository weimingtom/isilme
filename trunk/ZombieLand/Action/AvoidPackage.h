#ifndef AI_AVOID_PACKAGE_H
#define AI_AVOID_PACKAGE_H

#include <Isilme.h>
#include <Engine/include/AIPackage.h>
#include <Engine/Core/AIPackageDef.h>

#include "ZombieLand/Include/Definitions.h"

class AvoidPackage : public AIPackage
{
public:
	AvoidPackage();
	virtual ~AvoidPackage();

	/// Проверяем, есть ли поблизости враждебно настроенные агенты
	virtual bool CheckCondition();

	/// Создает и настраивает действие атаки цели
	virtual ActionPtr CreateAction();
protected:
private:
};

class AvoidPackageDef : public AIPackageDef
{
public:
	virtual AIPackagePtr CreatePackage();
};

#endif