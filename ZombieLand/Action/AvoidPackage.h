#ifndef AI_AVOID_PACKAGE_H
#define AI_AVOID_PACKAGE_H

#include "../include/Definitions.h"

class AvoidPackage : public AIPackage
{
public:
	AvoidPackage();
	virtual ~AvoidPackage();

	/// Проверяем, есть ли поблизости враждебно настроенные агенты
	virtual bool IsApplicable(BehaviourPtr behaviour) const override;

	/// Создает и настраивает действие атаки цели
	virtual ActionPtr CreateAction() const override;
protected:
private:
};

class AvoidPackageDef : public AIPackageDef
{
public:
	virtual AIPackagePtr CreatePackage();
};

#endif