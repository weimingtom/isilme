#include "Isilme.h"

Action::Action()
{
	/// Действие изначально не выпоняется
	mState = action::Ready;

	/// Установка временных параметров по умолчанию
	mBeginningTime = 0.0f;
	mDoingTime = 0.0f;
	mEndingTime = 0.0f;

	/// Сброс таймера
	mTime = 0.0f;

	mMask = 0;
}

Action::~Action()
{
}

void	Action::SetBeginningTime(float time)
{
	mBeginningTime = time;
}

void	Action::SetDoingTime(float time)
{
	mDoingTime = time;
}

void	Action::SetEndingTime(float time)
{
	mEndingTime = time;
}

void	Action::OnStart(BehaviourPtr behaviour)
{
	mBehaviour = behaviour;
	mState = action::Beginning;
	mTime = 0.0f;
	OnStart();
}

void	Action::SetParent(ActionPtr action)
{
	mParent = action;
}

ActionPtr	Action::GetParent()
{
	return mParent.lock();
}

bool	Action::IsEnabled()
{
	return true;
}

bool Action::IsActive()
{
	return mState != action::Done && mState != action::Ready && mState != action::Failed;
}

void Action::Stop()
{
	mTime = mBeginningTime + mEndingTime + mDoingTime;
	OnForceStop();
}

action::ActionState Action::GetState()
{
	return mState;
}

unsigned long Action::GetMask()
{
	return mMask;
}

EntityPtr	Action::GetActor()
{
	return mBehaviour.lock()->GetActor();
}

LevelPtr Action::GetLevel()
{
	return GetActor()->GetLevel();
}

float	Action::GetDoingTime()
{
	return mDoingTime;
}

bool Action::Update(float elapsedTime)
{
	mTime += elapsedTime;

	if (mState == action::Beginning)
	{
		UpdateOnBeginning(elapsedTime);
		if (mTime > mBeginningTime)
			mState++;
		if (mTime > mBeginningTime + mDoingTime)
			mState++;
		if (mTime > mBeginningTime + mDoingTime + mEndingTime)
			mState++;
	}

	if (mState == action::Doing)
	{
		UpdateOnDoing(elapsedTime);
		if (mTime > mBeginningTime + mDoingTime)
			mState++;
		if (mTime > mBeginningTime + mDoingTime + mEndingTime)
			mState++;
	}

	if (mState == action::Ending)
	{
		UpdateOnDoing(elapsedTime);
		if (mTime > mBeginningTime + mDoingTime + mEndingTime)
		{
			mState++;
			OnDone();
			mTime = 0.0f;
			return false;
		}
	}

	if (mState == action::Done)
		OnDone();

	return mState < action::Done;
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