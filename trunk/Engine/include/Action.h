#ifndef ACTION_H
#define ACTION_H

#include "Definitions.h"
#include "Engine/Action/Strategy.h"


namespace action
{
	enum ActionState
	{
		Ready,
		Beginning,
		Doing,
		Ending,
		Done,
		Failed
	};
};

/// Интерфейс действия
class IAction
{
	friend class Behaviour;
public:
	/// Итерация действия
	virtual bool Update(float elapsedTime) = 0;

	/// Выполняется в момент начала действия
	virtual void Stop() = 0;

	/// Возвращает состояние действия
	virtual action::ActionState GetState() = 0;

	/// @depricated
	virtual unsigned long GetMask() = 0;

	/// Проверяе активно ли действие
	virtual bool IsActive() = 0;

	/// Возвращает родительское действие
	virtual ActionPtr	GetParent() = 0;

	virtual void	SetParent(ActionPtr parent) = 0;
protected:
	/// Вызывается из Behaviour владельца
	virtual void	OnStart(BehaviourPtr behaviour) = 0;

};

/// @class Action
/// Класс описывает действие, совершаемое игровым объектом
class IsilmeExport  Action : public IAction
{
	friend class Behaviour;
public:

	
	Action();
	virtual ~Action();

	// Итерация. Возвращает 
	//	- true, если действие продолжается и 
	//	- false, если действие завершилось или перезаряжается
	virtual bool		Update(float elapsedTime);

	/// Получает уровень
	LevelPtr			GetLevel();

	/// Возвращает действующее лицо
	EntityPtr			GetActor();

	/// Возвращает состояние действия
	virtual action::ActionState		GetState();

	/// Останавливает действие
	virtual void		Stop();

	/// Возвращает и
	virtual bool			IsActive();

	/// Проверяет, возможно ли выполнение действия
	virtual bool	IsEnabled();
	
	unsigned long GetMask();

	
	/// Возвращает родительское действие
	virtual ActionPtr	GetParent();
protected:
	virtual void	SetParent(ActionPtr parent);

	/// Родительское действие
	ActionWPtr	mParent;

	unsigned long mMask;

	/// Таймер действия
	float mTime;

	/// Время подготовки действия
	float mBeginningTime;

	/// Время выполнения действия
	float mDoingTime;

	/// Время завершения действия
	float mEndingTime;

	/// Поведение сущности, выполняющей действие
	BehaviourWPtr mBehaviour;

	/// Состояние действия
	action::ActionState mState;

	int mGroup;

private:
	/// Вызывается из Behaviour владельца
	void	OnStart(BehaviourPtr behaviour);
protected:
	/// Подготовка действия
	virtual void UpdateOnBeginning(float elapsedTime)
	{
	}

	/// Выполнение действия
	virtual void UpdateOnDoing(float elapsedTime)
	{
	}

	/// Завершение действия
	virtual void UpdateOnEnding(float elapsedTime)
	{
	}

	/// Начало действия
	virtual void OnStart()
	{
	}

	virtual void OnForceStop()
	{
	}

	/// Окончание действия
	virtual void OnDone()
	{
	}
};

typedef std::list<ActionPtr> ActionList;
typedef std::map<std::string, ActionPtr> ActionMap;

action::ActionState& operator ++(action::ActionState& var);
action::ActionState& operator ++(action::ActionState& var, int c);

#endif