#include "TeddyTerror.h"
#include "Actions.h"
#include "Behaviours.h"
#include "Move.h"

// Block

BlockBehaviour::BlockBehaviour()
{

}

void BlockBehaviour::Apply()
{
	Box2DBody* body = (Box2DBody*)(GetActor()->GetBody());
	b2Fixture* fixture = body->GetBox2DBody()->GetFixtureList();

	b2Filter filter;
	filter.categoryBits = CategoryBlock;
	filter.maskBits = MaskBlock;
	filter.groupIndex = 0;

	for (fixture; fixture; fixture = fixture->GetNext())
	{
		fixture->SetFilterData(filter);
	}

	GetActor()->SetGraphics("IdleLeft");
}

BlockBehaviour::~BlockBehaviour()
{
}

// Decoration

DecorationBehaviour::DecorationBehaviour()
{

}

void DecorationBehaviour::Apply()
{
	Box2DBody* body = (Box2DBody*)(GetActor()->GetBody());
	b2Fixture* fixture = body->GetBox2DBody()->GetFixtureList();

	b2Filter filter;
	filter.categoryBits = CategoryDecoration;
	filter.maskBits = MaskDecoration;
	filter.groupIndex = 0;

	for (fixture; fixture; fixture = fixture->GetNext())
	{
		fixture->SetFilterData(filter);
	}
}

DecorationBehaviour::~DecorationBehaviour()
{
}

// DestroyableObject

DestroyableObject::DestroyableObject()
{
	mGroup		= BehaviourDestroyable;
	mMaxHealth	= 100.0f;
	mHealth		= mMaxHealth;

	DeathParams params;
	params.direction = mDirection;
	StartAction("Die", (void*)&params);

	AddAction("Die", new Die());
}

DestroyableObject::~DestroyableObject()
{
}

void	DestroyableObject::SetParams(StringMap& params)
{
	for (StringMap::iterator it = params.begin(); it != params.end(); ++it)
	{
		if (it->first == "Health")
		{
			sscanf_s(it->second.c_str(), "%f", &mHealth);
		}
		else
		{
		}
	}
}

DirectionType	DestroyableObject::GetDirection()
{
	return mDirection;
}

void	DestroyableObject::SetDirection(DirectionType value)
{
	mDirection = value;
}

float	DestroyableObject::GetHealth()
{
	return mHealth;
}

float	DestroyableObject::GetMaxHealth()
{
	return mMaxHealth;
}

void	DestroyableObject::SetHealth(float value)
{
	mHealth = min(value, mMaxHealth);
}

void	DestroyableObject::SetMaxHealth(float value)
{
	mMaxHealth = value;
	mHealth = min(mHealth, mMaxHealth);
}

float	DestroyableObject::GetNormalResistance(b2Fixture* part)
{
	if (part == 0 && mNormalResistance.size() > 0)
	{
		return mNormalResistance.begin()->second;
	}

	ResistanceMap::iterator it = mNormalResistance.find(part);
	if (it == mNormalResistance.end())
	{
		mNormalResistance[part] = 0.0f;
		return 0.0f;
	}
	else
	{
		return it->second;
	}
}

float	DestroyableObject::GetFireResistance(b2Fixture* part)
{
	if (part == 0 && mFireResistance.size() > 0)
	{
		return mFireResistance.begin()->second;
	}

	ResistanceMap::iterator it = mFireResistance.find(part);
	if (it == mFireResistance.end())
	{
		mFireResistance[part] = 0.0f;
		return 0.0f;
	}
	else
	{
		return it->second;
	}
}

void	DestroyableObject::Damage(b2Fixture* part, float normal, float fire)
{
	mHealth -= (1.0f - GetNormalResistance(part)) * normal;
	mHealth -= (1.0f - GetFireResistance(part)) * fire;

	if (mHealth <= 0.0f)
	{
		DeathParams params;
		params.direction = mDirection;
		StartAction("Die", (void*)(&params));
	}
}

// Bullets


// One-sinde platforms

OneSidePlatformBehaviour::OneSidePlatformBehaviour()
{
	mGroup = BehaviourPlatform;
}

OneSidePlatformBehaviour::~OneSidePlatformBehaviour()
{
}

void OneSidePlatformBehaviour::HandleContact(b2Contact* contact, const b2Manifold* oldManifold, Entity* other)
{
	b2WorldManifold manifold;
	contact->GetWorldManifold(&manifold);
	if (manifold.normal.y > 0.0f)
		contact->SetEnabled(false);
}

// Creatures

CreatureBehaviour::CreatureBehaviour()
{
	mGroup = BehaviourDestroyable | BehaviourCreature;
	mHealth = 100.0f;


}

void CreatureBehaviour::Apply()
{
	Box2DBody* body = (Box2DBody*)(GetActor()->GetBody());
	b2Fixture* fixture = body->GetBox2DBody()->GetFixtureList();

	b2Filter filter;
	filter.categoryBits = CategoryCreature;
	filter.maskBits = MaskCreature;
	filter.groupIndex = 0;

	for (fixture; fixture; fixture = fixture->GetNext())
	{
		fixture->SetFilterData(filter);
	}
}

CreatureBehaviour::~CreatureBehaviour()
{
}

// Monsters

MonsterBehaviour::MonsterBehaviour() : CreatureBehaviour()
{
	AddAction("Move", new Move());
	AddAction("Up", new Jump());
	AddAction("Die", new Die());
}

MonsterBehaviour::~MonsterBehaviour()
{
}

void MonsterBehaviour::Think(float elapsedTime)
{
	if (mActiveActions.size() == 0)
	{
		MoveParams p;
		p.velocity = 1.0f;
		p.direction = rand() % 2 ? DirectionLeft : DirectionRight;

		StartAction("Move", (void*)&p);
	}
}

// Players

