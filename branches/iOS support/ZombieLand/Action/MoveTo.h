#ifndef ACTION_MOVETO_H
#define ACTION_MOVETO_H

#include "../include/Definitions.h"

namespace action
{
	/// Двигаться к цели
	class MoveTo : public Action
	{
	public:
		MoveTo();
		virtual ~MoveTo();

		/// Установить цель - объект
		void	SetTarget(EntityPtr	entity);

		/// Установить цель - точка
		void	SetTarget(Vector2 point);

		virtual void	OnStart();
		virtual void	OnUpdate(float elapsedTime);
		virtual void	OnDone();
		virtual void	OnForceStop();
	private:
		EntityPtr	mEntityTarget;
		Vector2		mPointTarget;

		behaviour::CreaturePtr	mCreature;
	};
};

#endif