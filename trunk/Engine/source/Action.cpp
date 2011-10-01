#include "Isilme.h"

Action::Action()
{
	/// Действие изначально не выпоняется
	mState = action::Ready;
	
	/// Сброс таймера
	mTimer = 0.0f;

	/// По умолчанию действие длится бесконечно долго
	mDuration = -1.0f;
}

Action::~Action()
{
}

void	Action::SetDuration(float duration)
{
	mDuration = duration;
}

float	Action::GetDuration()
{
	return mDuration;
}

float	Action::GetTimer()
{
	return mTimer;
}

void	Action::OnStart(BehaviourPtr behaviour)
{
	mBehaviour = behaviour;
	mEntity = behaviour->GetActor();
	mState = action::Doing;
	mTimer = 0.0f;

	OnStart();
}

ActionPtr	Action::GetParent()
{
	return mParent.lock();
}

bool Action::IsActive()
{
	return mState == action::Doing;
}

void Action::Stop()
{
	mState = action::Done;
	OnForceStop();
}

action::ActionState Action::GetState()
{
	return mState;
}

EntityPtr	Action::GetActor()
{
	return mBehaviour.lock()->GetActor();
}

EntityPtr	Action::GetEntity()
{
	return mEntity.lock();
}

LevelPtr Action::GetLevel()
{
	return GetEntity()->GetLevel();
}

bool Action::Update(float elapsedTime)
{
	mTimer += elapsedTime;

	if (mState == action::Doing)
	{
		if (mChildActions.size() > 0)
		{
			UpdateChildActions(elapsedTime);
		}
		else
		{
			OnUpdate(elapsedTime);
		}

		// Проверка по таймеру
		if (mDuration != -1)
		{
			if (mTimer > mDuration)
				mState = action::Done;
		}

		if (mState == action::Done)
		{
			OnDone();
		}
	}

	return mState != action::Done;
}

void	Action::UpdateChildActions(float elapsedTime)
{
	ActionSet::iterator it = mChildActions.begin();

	while (it != mChildActions.end())
	{
		(*it)->Update(elapsedTime);
		OnChildUpdated(*it, elapsedTime);

		if (!(*it)->IsActive())
		{
			it = mChildActions.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void	Action::StartChildAction(ActionPtr action)
{
	action->mParent = shared_from_this();
	action->OnStart(mBehaviour.lock());
	mChildActions.insert(action);
}

void	Action::OnDone()
{
}

void	Action::OnStart()
{
}

void	Action::OnUpdate(float elapsedTime)
{
}

void	Action::OnForceStop()
{
}

void	Action::OnChildUpdated(ActionPtr childAction, float elapsedTime)
{
}

bool	Action::DoneCondition()
{
	return false;
}

action::ActionState& operator ++(action::ActionState& var)
{
	var = (action::ActionState)((int)(var)+1);
	return var;
}

action::ActionState& operator ++(action::ActionState& var, int c)
{
	var = (action::ActionState)((int)(var)+1);
	return var;
}