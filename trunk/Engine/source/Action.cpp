#include "Isilme.h"

Action::Action()
{
	/// �������� ���������� �� ����������
	mState = action::Ready;

	/// ��������� ��������� ���������� �� ���������
	mBeginningTime = 0.0f;
	mDoingTime = 0.0f;
	mEndingTime = 0.0f;

	/// ����� �������
	mTime = 0.0f;

	mMask = 0;
}

Action::~Action()
{
}

void	Action::OnStart(BehaviourPtr behaviour)
{
	mBehaviour = behaviour;
	mState = action::Beginning;
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

bool Action::Update(float elapsedTime)
{
	mTime += elapsedTime;

	if (mState == action::Beginning)
	{
		UpdateOnBeginning(elapsedTime);
		if (mTime > mBeginningTime)
			mState++;
	}

	if (mState == action::Doing)
	{
		UpdateOnDoing(elapsedTime);
		if (mTime > mBeginningTime + mDoingTime)
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
		}
	}

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