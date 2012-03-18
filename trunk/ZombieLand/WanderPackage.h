#ifndef AI_PACKAGES_WANDER_H
#define AI_PACKAGES_WANDER_H

#include "../Definitions.h"

class WanderPackage : public AIPackage
{
public:
	WanderPackage();
	virtual ~WanderPackage();

	/// ������� ����������� �������� ��� ������
	virtual ActionPtr	CreateAction();
};

class WanderPackageDef : public AIPackageDef
{
	virtual AIPackagePtr CreatePackage();
};
#endif