#include "Isilme.h"
#include <luabind/luabind.hpp>
#include <luabind/lua_include.hpp>

Trigger::Trigger(TriggerDefinition* def)
{
	isActivated = false;
	mTimer = -1.0f;
	mReactivateTime = def->ReacticvateTime;
	mActivateMask	= def->ActivateMask;
	mActivationFunction = ScriptAPI::MakeFunction("trigger, target", def->ActivationFunction);
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

EntityPtr	Trigger::GetTarget()
{
	return mTarget;
}

void	Trigger::Activate(EntityPtr target)
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
		if (mActivationFunction)
		{
			mActivationFunction(GetActor(), GetTarget());
		}
		isActivated = false;
		mTarget.reset();
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
		Activate(other->GetBehaviour()->GetActor());
	}
}

bool	Trigger::IsActivated()
{
	return isActivated;
}

void	Trigger::SetActivationFunction(std::string function)
{
	mActivationFunction = ScriptAPI::MakeFunction("trigger, target", function);
}

void	Trigger::SetReactivateTime(float time)
{
	mReactivateTime = time;
}

BehaviourPtr TriggerDefinition::Create()
{
	Trigger* trigger = new Trigger(this);
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
