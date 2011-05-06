#include "Isilme.h"

Trigger::Trigger()
{
	isActivated = false;
	mActivationFunction = "";
	mTarget = 0;
	mTimer = -1.0f;
	mReactivateTime = 0.0f;
}

Trigger::~Trigger()
{
}

int Trigger::GetActivateMask()
{
	return mActivateMask;
}

void	Trigger::SetActivateMask(int mask)
{
	mActivateMask = mask;
}

Entity*	Trigger::GetTarget()
{
	return mTarget;
}

void	Trigger::Activate(Entity* target)
{
	mTarget = target;
	isActivated = true;
}

void	Trigger::Think(float elapsedTime)
{
	if (IsActivated())
	{
		Lua* lua = Engine::GetSingleton()->GetLua();
		bool result;
		if (GetActivationFunction() != "")
		{
			lua->CallFunction(
				GetActivationFunction().c_str(),	// Имя функции
				result,								// Результат
				GetActor()->GetName(),				// Имя триггера
				GetTarget()->GetName()				// Имя объекта
			);
		}
		isActivated = false;
		mTarget = 0;
		mTimer = mReactivateTime;
	}

	if (mTimer > 0.0f)
	{
		mTimer -= elapsedTime;
	}

}

float	Trigger::GetTimer()
{
	return mTimer;
}

void	Trigger::HandleContact(b2Contact* contact, const b2Manifold* oldManifold, Entity* other)
{
	if ((contact->GetFixtureA()->GetFilterData().categoryBits & GetActivateMask()) ||
		(contact->GetFixtureB()->GetFilterData().categoryBits & GetActivateMask()))
	{
		contact->SetEnabled(false);
		if (mTimer > 0.0f)
			return;
		Activate(other);
	}
}

std::string	Trigger::GetActivationFunction()
{
	return mActivationFunction;
}

bool	Trigger::IsActivated()
{
	return isActivated;
}

void	Trigger::SetActivationFunction(std::string function)
{
	mActivationFunction = function;
}

void	Trigger::SetReactivateTime(float time)
{
	mReactivateTime = time;
}

BehaviourPtr TriggerDefinition::Create()
{
	Trigger* trigger = new Trigger();
	trigger->SetActivationFunction(ActivationFunction);
	trigger->SetReactivateTime(ReacticvateTime);
	trigger->SetActivateMask(ActivateMask);
	return BehaviourPtr(trigger);
}

void TriggerDefinition::Parse(TiXmlElement* element)
{
	ActivationFunction = element->Attribute("ActivationFunction");
	ReacticvateTime = 0;
	ActivateMask = 0xffffffff;
	element->QueryFloatAttribute("ReactivateTime", &ReacticvateTime);
	element->QueryIntAttribute("ActivateMask", &ActivateMask);
}
