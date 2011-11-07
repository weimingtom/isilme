#ifndef AI_AVOID_PACKAGE_H
#define AI_AVOID_PACKAGE_H

#include <Isilme.h>
#include <Engine/include/AIPackage.h>
#include "ZombieLand/Include/Definitions.h"

class AvoidPackage : public AIPackage
{
public:
	AvoidPackage();
	virtual ~AvoidPackage();

	/// ���������, ���� �� ���������� ��������� ����������� ������
	virtual bool CheckCondition(BehaviourPtr behaviour);

	/// ������� � ����������� �������� ����� ����
	virtual ActionPtr CreateAction();
protected:
private:
};

#endif