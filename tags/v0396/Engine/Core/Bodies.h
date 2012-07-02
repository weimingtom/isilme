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
#ifndef BODIES_H
#define BODIES_H

#include "Definitions.h"
#include "Collisions.h"
#include "Entity.h"
#include <TinyXML.h>

/// @class BodyDef
/// Определение тела. 
/// Определяет тип тела и свойства
class ISILME_API BodyDef
{
public:
	enum BodyType
	{
		SimpleBody	= 0,
		Box2DBody	= 1
	};

	/// Тип физической модели, который нужно создать
	BodyType	Type;

	/// Мир в котором находится физическая модель
	b2World*	World;

	/// Определение модели для Box2D
	b2BodyDef		B2DBodyDef;

	/// Определение геометрии для Box2D
	FixtureDefList	B2DFixtures;

	BodyDef();
	virtual void	Parse(TiXmlElement* bodyElement);
protected:
	void			ParseB2DBody(TiXmlElement* bodyElement);
	b2FixtureDef*	ParseB2DFixture(TiXmlElement* fixtureElement);
};


/// @interface Body
/// Физическая модель объекта описывает расположение объекта в пространстве игрового мира.
class ISILME_API Body
{
public:
	Body();
	virtual Vector2&	GetPosition() = 0;
	virtual void		SetPosition(Vector2& position) = 0;
	virtual float		GetAngle() = 0;
	virtual void		SetAngle(float angle) = 0;
	BodyDef::BodyType	GetType();
	virtual void		SetEntity(Entity* entity) = 0;
	virtual Entity*		GetEntity() = 0;
	virtual void		SetActive(bool flag);
	virtual void		SetLinearVelocity(Vector2& velocity) = 0;
	virtual Vector2		GetLinearVelocity() = 0;
	virtual Fixture*	GetFixture(std::string& fixture) = 0;

	virtual void		AttachToLevel(LevelPtr level) = 0;
	float GetScale();
	void SetScale(float value);
	void Scale(float value);
	virtual ~Body();
protected:
	BodyDef::BodyType	mType;
	virtual void OnScale(float oldScale, float scale);
private:
	float mScale;
};

/// @class Box2dBody
/// Физическая модель, основанная на движке Box2D. Объекты с данной физической моделью
/// могут сталкиваться между собой, обладают массой
class ISILME_API Box2DBody : public Body
{
public:
	Box2DBody(BodyDef* def);
	virtual ~Box2DBody();
	virtual Vector2&	GetPosition();
	virtual float		GetAngle();
	virtual void		SetPosition(Vector2& position);
	virtual void		SetAngle(float angle);
	b2Body*				GetBox2DBody();
	virtual void		SetEntity(Entity* entity);
	virtual Entity*		GetEntity();
	virtual void		SetActive(bool flag);
	virtual void		SetLinearVelocity(Vector2& velocity);
	virtual Vector2		GetLinearVelocity();
	virtual Fixture*	GetFixture(std::string& name);
	virtual void		AttachToLevel(LevelPtr level);
protected:
	virtual Fixture*	CreateFixture(std::string& name, b2FixtureDef* fixtureDef);
	virtual void		DestroyFixture(std::string& name);
	virtual void		DestroyFixture(Fixture* fixture);
	virtual void		OnScale(float oldScale, float scale);
	/// Тело Box2D
	b2Body*				mBody;

	/// @depricated
	FixtureMap			mFixtures;

	/// Определение тела Box2D
	BodyDef*			mBodyDefinition;

	/// Сущность, к которойпривязано тело
	Entity*		mEntity;

	/// The offline position
	Vector2 mOfflinePosition;

	/// The offline angle
	float mOfflineAngle;
};

/// @class SimpleBody
/// Физическая модель тело-точка. Объекты обладают только координатами и углом поворота, 
/// не могут сталкиваться между собой и не обладают массой
class ISILME_API SimpleBody : public Body
{
public:
	SimpleBody();
	virtual ~SimpleBody();
	virtual Vector2&	GetPosition();
	virtual float		GetAngle();
	virtual void		SetPosition(Vector2& position);
	virtual void		SetAngle(float angle);
	virtual void		SetEntity(Entity* entity);
	virtual Entity*		GetEntity();
	virtual void		SetLinearVelocity(Vector2& velocity);
	virtual Vector2		GetLinearVelocity();
	virtual Fixture*	GetFixture(std::string& fixture);
	virtual void		AttachToLevel(LevelPtr level);
protected:
	Vector2				mPosition;
	float				mAngle;
	Entity*				mEntity;
};

#endif