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
#include "IsilmePCH.h"
#include "Trigger.h"
#include "ScriptAPI.h"
#include "Core/Engine.h"

Trigger::Trigger(TriggerDefinition* def) : Behaviour(def)
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

void	Trigger::OnUpdate(float elapsedTime)
{
	if (IsActivated())
	{
		lua_State* state = Engine::GetSingleton()->GetLua();
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
