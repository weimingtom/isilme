/// ****************************** Module Header ******************************
/// @file  Behaviours.h
///	Project:      Teddy Terror 
/// Copyright (c) Ofiel.
///
/// Модуль содержит описание поведений объектов.
///
/// ***************************************************************************

#ifndef GAME_BEHAVIOURS_H
#define GAME_BEHAVIOURS_H

#include <set>
#include <map>
#include <Isilme.h>
#include "Definitions.h"

/// @class DestroyableObject
/// Уничтожаемый объект.
/// Умеет получать повреждения и споротивляться им.
/// Разрушаемый объект может состоять из нескольких частей, 
/// каждая из котрых обладает своей сопротивляемостью урону.
class DestroyableObject : public Behaviour
{
public:
	DestroyableObject();
	virtual ~DestroyableObject();

	/// Возвращает здоровье объекта
	float			GetHealth();

	/// Устанавливает здоровье объекта
	void			SetHealth(float value);

	/// Возвращает максимум здоровья
	float			GetMaxHealth();

	/// Устанавливает максимум здоровья
	void			SetMaxHealth(float value);

	/// Возвращает сопротивляемость части тела обычному урону
	virtual float	GetNormalResistance(b2Fixture* part);

	/// Возвращает сопротивляемость части тела огню
	virtual float	GetFireResistance(b2Fixture* part);

	/// Наносит повреждение объекту
	virtual void	Damage(b2Fixture* part, float nornmal, float fire);

	/// Возвращает направление объекта
	DirectionType	GetDirection();

	/// Устанавливат направление объека 
	void			SetDirection(DirectionType value);

	virtual void	SetParams(StringMap& params);
protected:
	typedef std::map<b2Fixture*, float>	ResistanceMap;
	float			mHealth;
	float			mMaxHealth;
	bool			isAlive;
	ResistanceMap	mNormalResistance;
	ResistanceMap	mFireResistance;
	DirectionType	mDirection;
};

/// @class DecorationBeahaviour
/// Класс описывает разрушаемую декорацию
class DecorationBehaviour : public DestroyableObject
{
public:
	DecorationBehaviour();
	virtual ~DecorationBehaviour();
protected:
	virtual void Apply();
};


class BlockBehaviour : public DestroyableObject
{
public:
	BlockBehaviour();
	virtual ~BlockBehaviour();
protected:
	virtual void Apply();
};

/// @class OneSidePlatformBehaviour
/// Поведение односторонней платформы
/// Объекты падающие на платформу сверху остаются на ней, в то время
/// как тела падающие на платформу снизу пролетают ее насквозь
class OneSidePlatformBehaviour : public Behaviour
{
public:
	OneSidePlatformBehaviour();
	virtual ~OneSidePlatformBehaviour();
	// Столконовения с другими объектами должны происходить, только если объект падает сверху
	virtual void	HandleContact(b2Contact* contact, const b2Manifold* oldMainfold, Entity* other);
protected:
};

/// @class CreatureBehaviour
/// Поведение персонажа
/// Персонажи принимают решения, совершают различные действия
class CreatureBehaviour : public DestroyableObject
{
public:
	CreatureBehaviour();
	virtual ~CreatureBehaviour();
	// Возвращает здоровье существа
protected:
	virtual void		Apply();
};

/// @class MonsterBehaviour
/// Поведение монстра
/// Класс реализует поведение монстра
/// Монстр сам принимает решения
/// @todo:
/// В данный моvент решения принимаются случайно, а именно в какую сторону идти
class MonsterBehaviour : public CreatureBehaviour
{
public:
	MonsterBehaviour();
	virtual ~MonsterBehaviour();
	// Реализация управления
	virtual void	Think(float elapsedTime);
protected:
};

#endif