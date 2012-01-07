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