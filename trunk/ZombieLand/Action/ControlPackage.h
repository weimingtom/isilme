#ifndef AI_CONTROL_PACKAGE_H
#define AI_CONTROL_PACKAGE_H

#include <Isilme.h>
#include <Engine/include/AIPackage.h>
#include "ZombieLand/Include/Definitions.h"
#include "Engine/Core/AIPackageDef.h"

/// Пакет предоставляет возможность контролировать персонажа с помощью клавиатуры или геймпада
class ControlPackage : public AIPackage
{
public:
	ControlPackage();
	virtual ~ControlPackage();

	virtual ActionPtr CreateAction();

	virtual bool CheckCondition();
};

class ControlPackageDef : public AIPackageDef
{
public:
	virtual AIPackagePtr CreatePackage();
};
#endif