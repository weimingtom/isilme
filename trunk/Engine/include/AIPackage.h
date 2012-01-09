#ifndef ISILME_AIPACKAGE_H
#define ISILME_AIPACKAGE_H

#include "Definitions.h"
#include <luabind/luabind.hpp>

class ISILME_API AIPackage
{
	friend class Behaviour;
public:
	AIPackage();
	virtual ~AIPackage();

	/// Создает тактическое действие для агента
	virtual ActionPtr	CreateAction();

	/// Проверяет выполняется ли условие для агента
	virtual bool CheckCondition();

	/// Возвращает поведение, которому принадлежит пакет
	BehaviourPtr GetBehaviour();

	/// Возвращает сущность которой принадлежит пакет
	EntityPtr GetEntity();
private:
	/// Поведение
	BehaviourWPtr mBehaviour;
};

#endif