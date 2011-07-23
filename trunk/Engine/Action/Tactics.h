#ifndef ISILME_ACTION_TACTICS_H
#define ISILME_ACTION_TACTICS_H

#include "Definitions.h"
#include "Action.h"
#include "Strategy.h"

namespace action
{
	/// Тактическое длительное действие
	class IsilmeExport Tactics : public IAction, public IStrategy
	{	
	public:
		Tactics();
		virtual ~Tactics();

		/// Итерация обновленя тактики
		virtual bool Update(float elapsedTime);

		/// Принудительная остановка тактики
		virtual void Stop();

		/// Возвращает состояние тактического действия
		virtual action::ActionState GetState();

		/// @depricated
		virtual unsigned long GetMask();

		/// Проверяет активно ли действие
		virtual bool IsActive();

		/// Условие успешного завершения действия
		virtual bool	DoneCondition();

		/// Условие провала тактики
		virtual bool	FailCondition();

		///
		virtual void	OnThink(float elapsedTime);

		/// Выполняется в момент начала действия
		virtual void	OnStart();

		/// Выполняется в момент завершения действия
		virtual void	OnDone();

		/// Начинает выполнение дочернего действия
		virtual void	StartAction(ActionPtr action);

		virtual ActionPtr	GetParent();
	protected:
		virtual void	SetParent(ActionPtr parent);
		/// Вызывается из Behaviour владельца
		virtual void	OnStart(BehaviourPtr behaviour);
		BehaviourWPtr mBehaviour;
	private:
		action::ActionState mState;
		ActionWPtr mParent;
	};
};

#endif