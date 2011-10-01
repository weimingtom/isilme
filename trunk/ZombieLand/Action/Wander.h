#ifndef ACTION_WANDER_H
#define ACTION_WANDER_H

#include <Engine/include/Isilme.h>
#include "ZombieLand/Include/Definitions.h"

namespace action
{
	/// Персонаж блуждает без дела в пределах уровня
	/// Выбирается случайная достижимая точка, персонаж движется к ней используя MoveTo
	class Wander : public Action
	{
	public:
		Wander();
		virtual ~Wander();

		virtual void	OnStart();
		virtual void	OnUpdate(float elapsedTime);
		virtual void	OnDone();
		virtual void	OnForceStop();

		virtual bool	DoneCondition();
	protected:
		MoveToPtr	mMoveAction;
		Vector2		mTarget;
	};
};

#endif