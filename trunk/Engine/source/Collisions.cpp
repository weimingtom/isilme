#include "Isilme.h"

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