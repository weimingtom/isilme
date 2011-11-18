#include "IsilmePCH.h"

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
	mScale = 1.0f;
}

Entity::~Entity()
{
	delete mBody;
}

float	Entity::GetScale()
{
	return mScale;
}

void	Entity::SetScale(float value)
{
	ASSERT(value != 0);

	GetGraphics()->SetScale(value);
	GetBody()->SetScale(value);
	mScale = value;
}

void Entity::Scale(float value)
{
	SetScale(mScale * value);
}

void	Entity::SetPosition(Vector2 pos)
{
	SetPosition(pos.x, pos.y);
}

float	Entity::GetAngleTo(EntityPtr entity)
{
	return GetAngleTo(entity->GetPosition());
}

float		Entity::GetAngleTo(Vector2 point)
{
	Vector2 v = point - GetPosition();
	float l = v.Length();

	float sina = v.y / l;
	float cosa = v.x / l;

	if (cosa >= 0.0f)
		return asin(sina);
	else
		return 3.14f - asin(sina);
}

float	Entity::GetDistanceTo(EntityPtr entity)
{
	return GetDistanceTo(entity->GetPosition());
}

float	Entity::GetDistanceTo(Vector2 point)
{
	Vector2 v = GetPosition();
	v -= point;
	return v.Length();
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
	ASSERT(mBody);
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

std::string Entity::GetType()
{
	return mType;
}
