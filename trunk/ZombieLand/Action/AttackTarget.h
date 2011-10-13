#ifndef ZOMBIELAND_ACTION_ATTACKTARGET_H
#define ZOMBIELAND_ACTION_ATTACKTARGET_H

#include <Engine/include/Isilme.h>
#include "ZombieLand/Include/Definitions.h"

namespace action
{
	/// ��������� ����, ���� ��� � ����� ������������
	class AttackTarget : public Action
	{
	public:
		AttackTarget();
		virtual ~AttackTarget();

		/// ������������� ����
		void	SetTarget(behaviour::DestroyablePtr destroyable);

		/// ���������� ����
		behaviour::DestroyablePtr	GetTarget();

		virtual void	OnStart();
		virtual void	OnDone();
		virtual void	OnForceStop();
		virtual void	OnUpdate(float elapsedTime);
	protected:
		behaviour::DestroyablePtr mTarget;
		behaviour::CreaturePtr mCreature;
	};
};

#endif