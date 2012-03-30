#include "IsilmePCH.h"
#include "Behaviour.h"
#include "Action.h"
#include "FactoryManager.h"

BehaviourPtr Behaviour::New()
{
	return BehaviourPtr(new Behaviour(0));
}

Behaviour::Behaviour()
{
	isActive = true;
}

Behaviour::Behaviour(BehaviourDefinition* def)
{
	isActive = true;
}

Behaviour::~Behaviour()
{
}

void		Behaviour::SetActor(EntityPtr actor)
{
	mActor = actor;
}

EntityPtr		Behaviour::GetActor()
{
	return mActor.lock();
}

LevelPtr		Behaviour::GetLevel()
{
	return GetActor()->GetLevel();
}

void		Behaviour::Update(float elapsedTime)
{
	if (!isActive)
	{
		return;
	}

	OnUpdate(elapsedTime);
	UpdateActions(elapsedTime);
}

void		Behaviour::UpdateActions(float elapsedTime)
{
	ActionList::iterator it = mActiveActions.begin(); 
	while (it != mActiveActions.end())
	{
		(*it)->Update(elapsedTime);
		if ((*it)->GetState() == action::Done)
		{
			// Удаляем действие
			it = mActiveActions.erase(it);
		}
		else
		{
			// Продолжаем
			//mActionMask |= (*it)->GetMask();
			++it;
		}
	}
}

void		Behaviour::StartAction(ActionPtr action)
{
	mActiveActions.push_back(action);
	action->OnStart(shared_from_this());
}

void		Behaviour::SetActive(bool value)
{
	isActive = value;
}

bool		Behaviour::IsActive()
{
	return isActive;
}

void Behaviour::Customize(TiXmlElement* element)
{

}

int Behaviour::GetActiveActionsCount() const
{
	return mActiveActions.size();
}

void Behaviour::StopAllActions()
{
	for (ActionList::iterator it = mActiveActions.begin(); it != mActiveActions.end(); ++it)
	{
		(*it)->Stop();
	}
}

void BehaviourDefinition::Parse( TiXmlElement* element )
{

}
