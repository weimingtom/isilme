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
#ifndef TRIGGER_H
#define TRIGGER_H

#include "Definitions.h"
#include "Core/Behaviour.h"


class ISILME_API TriggerDefinition : public BehaviourDefinition
{
public:
	float ReacticvateTime;
	std::string ActivationFunction;
	int ActivateMask;

	virtual void Parse(TiXmlElement* element);

	virtual BehaviourPtr Create();
};

/// @class Trigger
/// Триггеры используются для реализации бонусов, ловушек, дверей и переключателей
/// @see TriggerGraphics
class ISILME_API Trigger : public Behaviour
{
public:
	Trigger(TriggerDefinition* def);
	virtual ~Trigger();

	/// Обрабатывает столкновения с другими объектами
	virtual void HandleContact(b2Contact* contact, const b2Manifold* oldManifold, Entity* other);

	/// Возвращает цель, которая активировала триггер
	EntityPtr		GetTarget();

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
	void		Activate(EntityPtr target);

	/// Является ли триггер активированнным
	bool		IsActivated();

	/// ПРоверяет состояние триггера и активирует его в случае необходимости
	virtual void	OnUpdate(float elapsedTime);

private:
	/// Функция активации триггера
	luabind::object mActivationFunction;

	/// Время реактивации триггера
	float		mReactivateTime;

	/// Таймер триггера
	float		mTimer;

	/// Флаг активации триггера
	bool		isActivated;

	/// Цель, захваченная триггером
	EntityPtr		mTarget;

	/// Маска активации триггера
	int mActivateMask;
};


#endif