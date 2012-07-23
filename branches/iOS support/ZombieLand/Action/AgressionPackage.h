#ifndef AI_AGRESSION_PACKAGE_H
#define AI_AGRESSION_PACKAGE_H

#include "../include/Definitions.h"
#include "AttackTarget.h"

/// Пакет ИИ, отвечающий за нападение на других агентов
class AgressionPackage : public AIPackage
{
public:
	AgressionPackage();
	virtual ~AgressionPackage();

	/// Проверяем, есть ли поблизости враждебно настроенные агенты
	virtual bool IsApplicable(BehaviourPtr b) const override;

	/// Создает и настраивает действие атаки цели
	virtual ActionPtr CreateAction() const override;
protected:
private:
};

class AgressionPackageDef : public AIPackageDef
{
	virtual AIPackagePtr CreatePackage();
};

#endif