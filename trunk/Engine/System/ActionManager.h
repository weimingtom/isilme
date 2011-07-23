#ifndef ISILME_ACTION_MANAGER_H
#define ISILME_ACTION_MANAGER_H

/// @class AсtionMAnager
/// Менеджер действий
/// @details
/// Контейнер для действий, который используется моделью поведения для обработки действий
class ActionManager
{
public:
	ActionManager();
	virtual ~ActionManager();

	/// Обновляет действия, на которых сосредоточено внимание агента
	void	Update(float elapsedTime);
private:
	/// Набор действий, на которых сосредоточено внимание агента
	ActionSet	mAttention;
};

#endif