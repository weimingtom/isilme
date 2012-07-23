#ifndef AI_AGRESSION_PACKAGE_H
#define AI_AGRESSION_PACKAGE_H

#include "../include/Definitions.h"
#include "AttackTarget.h"

/// ����� ��, ���������� �� ��������� �� ������ �������
class AgressionPackage : public AIPackage
{
public:
	AgressionPackage();
	virtual ~AgressionPackage();

	/// ���������, ���� �� ���������� ��������� ����������� ������
	virtual bool IsApplicable(BehaviourPtr b) const override;

	/// ������� � ����������� �������� ����� ����
	virtual ActionPtr CreateAction() const override;
protected:
private:
};

class AgressionPackageDef : public AIPackageDef
{
	virtual AIPackagePtr CreatePackage();
};

#endif