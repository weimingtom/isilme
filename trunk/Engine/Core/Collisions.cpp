//  Copyright (C) 2010-2012 Alexander Alimov
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
#include "Behaviour.h"

Box2DEngine* Box2DEngine::mInstance = 0;

// Box2DEngine
Box2DEngine::Box2DEngine()
{
	b2Vec2	gravity(0.0f, 1.8f);
	bool	doSleep = true;
}

Box2DEngine::~Box2DEngine()
{
}

b2World* Box2DEngine::CreateWorld()
{
	b2Vec2	gravity(0.0f, 9.8f);
	bool	doSleep = true;

	b2World*				world				= new b2World(gravity, doSleep);
	ContactListener*		contactListener		= new ContactListener();
	ContactFilter*			contactFilter		= new ContactFilter();
	DestructionListener*	destructionListener	= new DestructionListener();

	world->SetContactListener(contactListener);
	world->SetContactFilter(contactFilter);

	return world;
}

Box2DEngine* Box2DEngine::GetSingleton()
{
	if (!mInstance)
		mInstance = new Box2DEngine();
	return mInstance;
}

// ContactListener
ContactListener::ContactListener()
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldMainfold)
{
	Entity* entityA = (Entity*)(contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* entityB = (Entity*)(contact->GetFixtureB()->GetBody()->GetUserData());

	BehaviourPtr behaviourA = entityA->GetBehaviour();
	if (behaviourA)
		behaviourA->HandleContact(contact, oldMainfold, entityB);
	BehaviourPtr behaviourB = entityB->GetBehaviour();
	if (behaviourB)
		behaviourB->HandleContact(contact, oldMainfold, entityA);
}

// DestructionListener
DestructionListener::DestructionListener()
{
}

DestructionListener::~DestructionListener()
{
}

void DestructionListener::SayGoodbye(b2Joint* joint)
{
}

void DestructionListener::SayGoodbye(b2Fixture* fixture)
{
}

// ContactFilter
ContactFilter::ContactFilter()
{
}

ContactFilter::~ContactFilter()
{
}

bool ContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	const b2Filter& filter1 = fixtureA->GetFilterData();
	const b2Filter& filter2 = fixtureB->GetFilterData();

	if (filter1.groupIndex == filter2.groupIndex &&
		filter1.groupIndex != 0)
		{
			return filter1.groupIndex > 0;
		}

	bool collide = (filter1.maskBits & filter2.categoryBits) != 0 &&
					(filter1.categoryBits & filter2.maskBits) != 0;

	return collide;
}