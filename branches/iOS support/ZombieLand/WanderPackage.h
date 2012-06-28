#ifndef AI_PACKAGES_WANDER_H
#define AI_PACKAGES_WANDER_H

#include "../Definitions.h"

class WanderPackage : public AIPackage
{
public:
	WanderPackage();
	virtual ~WanderPackage();

	/// Создает тактическое действие для агента
	virtual ActionPtr	CreateAction() const override;

	virtual bool IsApplicable(BehaviourPtr behaviour) const override;
};

class WanderPackageDef : public AIPackageDef
{
	virtual AIPackagePtr CreatePackage();
};
#endif