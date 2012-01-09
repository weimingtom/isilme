#ifndef ISILME_AIPACKAGE_H
#define ISILME_AIPACKAGE_H

#include "Definitions.h"
#include <luabind/luabind.hpp>

class ISILME_API AIPackage
{
	friend class Behaviour;
public:
	AIPackage();
	virtual ~AIPackage();

	/// ������� ����������� �������� ��� ������
	virtual ActionPtr	CreateAction();

	/// ��������� ����������� �� ������� ��� ������
	virtual bool CheckCondition();

	/// ���������� ���������, �������� ����������� �����
	BehaviourPtr GetBehaviour();

	/// ���������� �������� ������� ����������� �����
	EntityPtr GetEntity();
private:
	/// ���������
	BehaviourWPtr mBehaviour;
};

#endif