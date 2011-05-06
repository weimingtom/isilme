#ifndef ISILME_ACTION_TACTICS_H
#define ISILME_ACTION_TACTICS_H

#include "Definitions.h"
#include "Action.h"
//#include "IStrategy.h"

namespace action
{
	/// Тактическое длительное действие
	class IsilmeExport Tactics : public IAction
	{	
	public:
		Tactics();
		virtual ~Tactics();

		virtual bool Update(float elapsedTime);
		virtual void Stop();
		virtual action::ActionState GetState();
		virtual unsigned long GetMask();
		virtual bool IsActive();

		virtual bool	DoneCondition();
		virtual bool	FailCondition();
		virtual void	OnThink(float elapsedTime);
		virtual void	OnStart();
		virtual void	OnDone();
	protected:
		/// Вызывается из Behaviour владельца
		virtual void	OnStart(BehaviourPtr behaviour);
		BehaviourWPtr mBehaviour;
	private:
		action::ActionState mState;
	};
};

#endif