#include "Isilme.h"

EntityPtr Entity::New(LevelPtr level, BehaviourPtr behaviour, Body* body, GraphicsPtr graphics)
{
	EntityPtr entity(new Entity());

	entity->mLevel = level;
	// Настраиваем графику
	entity->mGraphics = graphics;
	entity->mGraphics->mEntity = entity;

	// Настраиваем физику
	entity->mBody = body;
	entity->mBody->SetEntity(entity.get());

	// Настраиваем поведение
	entity->mBehaviour = behaviour;
	entity->mBehaviour->SetActor(entity);

	return entity;
}

// Entity

Entity::Entity() :
	isRemoved(false),
	isBodyRemoved(false),
	removeJoints(false)
{
	
}

Entity::~Entity()
{
	delete mBody;
}

LayerPtr	Entity::GetLayer()
{
	return mLayer.lock();
}

void	Entity::OnAddedToLayer(LayerPtr layer)
{
	mLayer = layer;
}

void	Entity::RemoveJoints()
{
	removeJoints = true;
}

LevelPtr			Entity::GetLevel()
{
	return mLevel.lock();
}

void			Entity::Update(float elapsedTime)
{
	mBehaviour->Update(elapsedTime);

	mGraphics->Update(elapsedTime);

	if (isBodyRemoved)
		mBody->SetActive(false);
	if (removeJoints)
	{
		b2Body* body = ((Box2DBody*)mBody)->GetBox2DBody();
		b2World* world = body->GetWorld();
		while (body->GetJointList())
		{
			world->DestroyJoint(body->GetJointList()->joint);
		}

		removeJoints = false;
	}
}

void			Entity::SetPosition(float x, float y)
{
	mBody->SetPosition(Vector2(x, y));
}

void			Entity::SetAngle(float angle)
{
	mBody->SetAngle(angle);
}

BehaviourPtr		Entity::GetBehaviour()
{
	return mBehaviour;
}

GraphicsPtr		Entity::GetGraphics()
{
	return mGraphics;
}

Vector2&		Entity::GetPosition()
{
	return mBody->GetPosition();
}

Body*			Entity::GetBody()
{
	return mBody;
}

float			Entity::GetAngle()
{
	return mBody->GetAngle();
}

void			Entity::Remove()
{
	isRemoved = true;
}

std::string		Entity::GetName()
{
	return mName;
}

bool			Entity::IsRemoved()
{
	return isRemoved;
}

void			Entity::RemoveBody()
{
	isBodyRemoved = true;
}