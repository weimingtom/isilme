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

///// Интерфейс действия
///// /// @depricated
//class IAction
//{
//	friend class Behaviour;
//public:
//	/// Начало действия
//	virtual void OnStart() = 0;
//
//	/// Завершение действия
//	virtual void OnDone() = 0;
//
//	/// Итерация действия
//	virtual bool Update(float elapsedTime) = 0;
//
//	/// Выполняется в момент начала действия
//	virtual void Stop() = 0;
//
//	/// Возвращает состояние действия
//	virtual action::ActionState GetState() = 0;
//
//	/// @depricated
//	virtual unsigned long GetMask() = 0;
//
//	/// Проверяе активно ли действие
//	virtual bool IsActive() = 0;
//
//	/// Возвращает родительское действие
//	virtual ActionPtr	GetParent() = 0;
//
//	virtual void	SetParent(ActionPtr parent) = 0;
//
//	virtual float	GetDoingTime() = 0;
//
//
//protected:
//	/// Вызывается из Behaviour владельца
//	virtual void	OnStart(BehaviourPtr behaviour) = 0;
//
//};

/// @class Action
/// Класс описывает действие, совершаемое игровым объектом
class IsilmeExport  Action : public boost::enable_shared_from_this<Action>
{
	friend class Behaviour;
public:
	Action();
	virtual ~Action();

	// Итерация. Возвращает 
	//	- true, если действие продолжается и 
	//	- false, если действие завершилось или перезаряжается
	virtual bool		Update(float elapsedTime);

	virtual void		OnUpdate(float elapsedTime);

	virtual void		OnStart();

	virtual void		OnForceStop();

	virtual void		OnDone();

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