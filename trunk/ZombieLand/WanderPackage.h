#ifndef AI_PACKAGES_WANDER_H
#define AI_PACKAGES_WANDER_H

#include <Isilme.h>
#include "Definitions.h"
#include <Engine/include/AIPackage.h>
#include "../Core/AIPackageDef.h"

class WanderPackage : public AIPackage
{
public:
	WanderPackage();
	virtual ~WanderPackage();

	/// Создает тактическое действие для агента
	virtual ActionPtr	CreateAction();
};

class WanderPackageDef : public AIPackageDef
{
	virtual AIPackagePtr CreatePackage();
};
#endif