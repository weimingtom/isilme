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
#ifndef ACTION_H
#define ACTION_H

#include "Definitions.h"

namespace action
{
	enum ActionState
	{
		Ready,
		Doing,
		Done
	};
};

/// @class Action
/// Класс описывает действие, совершаемое игровым объектом
class ISILME_API  Action : public boost::enable_shared_from_this<Action>
{
	friend class Behaviour;
public:
	static const int InfiniteDuration = -1;
	Action();
	virtual ~Action();

	// Итерация. Возвращает 
	//	- true, если действие продолжается и 
	//	- false, если действие завершилось или перезаряжается
	virtual bool		Update(float elapsedTime);

	/// Вызывается каждую итерацию
	virtual void		OnUpdate(float elapsedTime);

	/// Вызывается когда действие начинае выполнение
	virtual void		OnStart();

	/// Вызывается когда действие принудительно останавливается
	virtual void		OnForceStop();

	/// Вызывается когда действие успешно заканчивается
	virtual void		OnDone();

	/// Обратная связь для дочерних дейсвтий
	virtual void		OnChildUpdated(ActionPtr childAction, float elapsedTime);

	/// Получает уровень
	LevelPtr			GetLevel();

	/// Возвращает действующее лицо
	/// @depricated
	EntityPtr			GetActor();

	/// Возвращает действующее лицо
	EntityPtr			GetEntity();

	/// Возвращает состояние действия
	virtual action::ActionState		GetState();

	/// Останавливает действие
	virtual void		Stop();

	/// Возвращает и
	virtual bool			IsActive();

	/// Устанавливает продолжительность действия
	/// @param duration float продолжительность, если установлено -1 продолжительность не учитывается, если 0 OnUpdate не выполняется
	virtual void		SetDuration(float duration);

	/// Возвращает полную продолжительость действия
	virtual float		GetDuration();

	/// Возвращает текущую продолжительность дейсвтия
	virtual float		GetTimer();
	
	/// Возвращает true, если нужно завершить действие
	virtual bool		DoneCondition();
	
	/// Возвращает родительское действие
	virtual ActionPtr	GetParent();

	virtual void	StartChildAction(ActionPtr action);
protected:
	/// Родительское действие
	ActionWPtr	mParent;

	/// Таймер действия
	float mTimer;

	/// Продолжительность действия
	float mDuration;

	/// Сущность
	EntityWPtr mEntity;

	/// Поведение сущности, выполняющей действие
	BehaviourWPtr mBehaviour;

	/// Состояние действия
	action::ActionState mState;
	
	/// Вызывается из Behaviour владельца
	void	OnStart(BehaviourPtr behaviour);

	ActionSet mChildActions;
protected:
	void	UpdateChildActions(float elapsedTime);
};

typedef std::list<ActionPtr> ActionList;
typedef std::map<std::string, ActionPtr> ActionMap;

action::ActionState& operator ++(action::ActionState& var);
action::ActionState& operator ++(action::ActionState& var, int c);

#endif