#ifndef ZOMBIELAND_ACTION_ATTACKTARGET_H
#define ZOMBIELAND_ACTION_ATTACKTARGET_H

#include <Engine/include/Isilme.h>
#include "ZombieLand/Include/Definitions.h"

namespace action
{
	/// Атаковать цель, если она в зхоне досягаемости
	class AttackTarget : public Action
	{
	public:
		AttackTarget();
		virtual ~AttackTarget();

		/// Устанавливает цель
		void	SetTarget(behaviour::DestroyablePtr destroyable);

		/// Возвращает цель
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