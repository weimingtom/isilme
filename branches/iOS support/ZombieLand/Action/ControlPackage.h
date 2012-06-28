#ifndef AI_CONTROL_PACKAGE_H
#define AI_CONTROL_PACKAGE_H

#include "../Definitions.h"

/// Пакет предоставляет возможность контролировать персонажа с помощью клавиатуры или геймпада
class ControlPackage : public AIPackage
{
public:
	ControlPackage();
	virtual ~ControlPackage();

	virtual ActionPtr CreateAction() const override;

	virtual bool IsApplicable(BehaviourPtr behaviour) const override;
};

class ControlPackageDef : public AIPackageDef
{
public:
	virtual AIPackagePtr CreatePackage();
};
#endif