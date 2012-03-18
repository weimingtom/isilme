#include "IsilmePCH.h"
#include "EntityPalette.h"
#include "Core/EntityDefinition.h"
#include "Core/Behaviour.h"

EntityPalette::EntityPalette()
{

}

EntityPalette::~EntityPalette()
{

}

EntityPalette::EntityDefMap* EntityPalette::GetData() 
{
	return &mPalette;
}

EntityDefPtr EntityPalette::GetDefinition( std::string type ) 
{
	return mPalette[type];
}

void EntityPalette::Add( EntityDefPtr def )
{
	mPalette[def->GetType()] = def;
}

void EntityPalette::AddDefinition( EntityDefPtr def )
{
	mPalette[def->GetType()] = def;
}

void EntityPalette::Destroy( std::string id )
{
	EntityMap::iterator it = mEntites.find(id);
	if (it != mEntites.end())
	{
		mEntites.erase(it);
		it->second->Remove();
	}
}

void EntityPalette::Destroy( EntityPtr entity )
{
	entity->Remove();
	EntityMap::iterator it = mEntites.find(entity->GetName());
	if (it != mEntites.end())
		mEntites.erase(it);
}

EntityPtr EntityPalette::Create( std::string type, std::string id )
{
	EntityDefPtr def = GetDefinition(type);
	if (!def)
		return EntityPtr();

	Body* body;
	if (def->GetBodyDefinition()->Type == BodyDef::SimpleBody)
	{ 
		body = new SimpleBody();
	}
	else if (def->GetBodyDefinition()->Type == BodyDef::Box2DBody)
	{
		body = new Box2DBody(def->GetBodyDefinition());
	}

	GraphicsPtr graphics	= def->GetGraphicsDefinition()->Create();
	BehaviourPtr behaviour	= def->GetBehaviourDefinition()->Create();

	EntityPtr entity(new Entity());
	entity->mGraphics = graphics;
	entity->mBehaviour = behaviour;
	entity->mBody = body;

	graphics->mEntity = entity;
	behaviour->mActor = entity;
	body->SetEntity(entity.get());

	if (id == "")
	{
		std::string prefix = "GameObject_";
		char s[20];
		int n = 0;
		while (mEntites.find(prefix + _itoa(n, s, 16)) != mEntites.end())
			++n;
		id = prefix + _itoa(n, s, 16);
	}

	entity->mName = id;
	entity->mType = def->GetType();

	mEntites[id] = entity;

	return entity;
}

EntityPtr EntityPalette::GetEntity( std::string name )
{
	return mEntites[name];
}
