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
#include "Behaviour.h"

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
    Vector2 p(x, y);
	mBody->SetPosition(p);
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

const std::string& Entity::GetName() const
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

bool Entity::IsSerialisable()
{
	// TODO: Сделать декорации несериализуемыми
	return true;
}
