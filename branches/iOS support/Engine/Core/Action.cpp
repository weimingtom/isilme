//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#include "Behaviour.h"

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
			mChildActions.erase(it++);
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

void Action::SetTarget(EntityPtr target)
{
    mTarget = target;
}

EntityPtr Action::GetTarget()
{
    return mTarget;
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