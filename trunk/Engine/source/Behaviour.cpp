#include "Isilme.h"

unsigned long Behaviour::GetGroup()
{
	return mGroup;
}

BehaviourPtr Behaviour::New()
{
	return BehaviourPtr(new Behaviour());
}

Behaviour::Behaviour()
{
	mGroup = 0;
	isActive = true;
}

Behaviour::~Behaviour()
{
}

void		Behaviour::SetGroup(unsigned long group)
{
	mGroup = group;
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

	Think(elapsedTime);
	UpdateActions(elapsedTime);
}

void		Behaviour::UpdateActions(float elapsedTime)
{
	mActionMask = 0;

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

void	BehaviourDefinition::Parse(TiXmlElement* element)
{
	if (!element)
		return;
	/// Считываем аттрибуты объекта
	TiXmlElement* attributesElement = element->FirstChildElement("Attributes");
	if (attributesElement)
		ParseAttributes(attributesElement);

	/// Считываем пакеты ИИ
	TiXmlElement* aiElement = element->FirstChildElement("AI");
	if (aiElement)
		ParseAIPackages(aiElement);
}

void	BehaviourDefinition::ParseAttributes(TiXmlElement* attributesElement)
{
}

void	BehaviourDefinition::ParseAIPackages(TiXmlElement* aiElement)
{
}