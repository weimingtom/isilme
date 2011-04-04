﻿#ifndef TRIGGER_H
#define TRIGGER_H

#include "Definitions.h"
#include "Behaviour.h"

/// @class Trigger
/// Триггеры используются для реализации бонусов, ловушек, дверей и переключателей
/// @see TriggerGraphics
class IsilmeExport Trigger : public Behaviour
{
public:
	Trigger();
	virtual ~Trigger();

	/// Обрабатывает столкновения с другими объектами
	virtual void HandleContact(b2Contact* contact, const b2Manifold* oldManifold, Entity* other);

	/// Возвращает цель, которая активировала триггер
	Entity*		GetTarget();

	/// Возвращает функцию активации
	std::string GetActivationFunction();

	/// Устанавливает время реактивации
	void	SetReactivateTime(float time);

	/// Устанавливает функцию активации 
	void	SetActivationFunction(std::string function);

	/// Возвращает текущее значение таймера
	float		GetTimer();

	/// Возвращает маску активации, по которой проверяется должен ли сработать триггер 
	int GetActivateMask();

	/// Устанавливает маску активации триггера
	void	SetActivateMask(int mask);
protected:
	
	/// Активирует триггер
	void		Activate(Entity* target);

	/// Является ли триггер активированнным
	bool		IsActivated();

	/// ПРоверяет состояние триггера и активирует его в случае необходимости
	virtual void	Think(float elapsedTime);

private:
	/// Функция активации триггера
	std::string mActivationFunction;

	/// Время реактивации триггера
	float		mReactivateTime;

	/// Таймер триггера
	float		mTimer;

	/// Флаг активации триггера
	bool		isActivated;

	/// Цель, захваченная триггером
	Entity*		mTarget;

	/// Маска активации триггера
	int mActivateMask;
};

class IsilmeExport TriggerDefinition : public BehaviourDefinition
{
public:
	float ReacticvateTime;
	std::string ActivationFunction;
	int ActivateMask;

	virtual void Parse(TiXmlElement* element);

	virtual BehaviourPtr Create();
};

#endif