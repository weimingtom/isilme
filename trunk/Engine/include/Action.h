#ifndef ACTION_H
#define ACTION_H

#include "Definitions.h"


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

class IAction
{
	friend class Behaviour;
public:
	virtual bool Update(float elapsedTime) = 0;
	virtual void Stop() = 0;
	virtual action::ActionState GetState() = 0;
	virtual unsigned long GetMask() = 0;
	virtual bool IsActive() = 0;
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


protected:

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