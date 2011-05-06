#include "Isilme.h"
#include "Tactics.h"

namespace action
{
	Tactics::Tactics()
	{
		mState = action::Ready;
	}

	Tactics::~Tactics()
	{
	}

	bool Tactics::Update(float elapsedTime)
	{
		if (IsActive())
		{
			OnThink(elapsedTime);
		}

		if (DoneCondition())
		{
			mState = action::Done;
			OnDone();
		}
		else if (FailCondition())
		{
			mState = action::Failed;
		}

		return !(mState == action::Doing || mState == action::Failed);
	}

	void Tactics::Stop()
	{
		mState = action::Done;
		OnDone();
	}

	action::ActionState Tactics::GetState()
	{
		return mState;
	}

	unsigned long Tactics::GetMask()
	{
		return 0;
	}

	/// Вызывается из Behaviour владельца
	void	Tactics::OnStart(BehaviourPtr behaviour)
	{
		mState = action::Beginning;
		mBehaviour = behaviour;

		OnStart();
	}

	void	Tactics::OnThink(float elapsedTIme)
	{
	}

	bool	Tactics::DoneCondition()
	{
		return false;
	}

	bool	Tactics::FailCondition()
	{
		return false;
	}

	void	Tactics::OnStart()
	{
	}

	void	Tactics::OnDone()
	{
	}

	bool	Tactics::IsActive()
	{
		return (mState != action::Ready && mState != action::Done && mState != action::Failed);
	}
};