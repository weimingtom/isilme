#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <string>
#include <tinyxml.h>
#include "Definitions.h"
#include "Collisions.h"
#include "Entity.h"
#include "Engine/System/ActionManager.h"

#define BEHAVIOUR_GROUP_COMMON 0


/// class Behaviour
/// Класс описывает поведение игрового объекта,
class IsilmeExport Behaviour : public boost::enable_shared_from_this<Behaviour>
{
	friend class Entity;
	friend class Tactics;
public:
	static BehaviourPtr New();

	virtual ~Behaviour();

	/// Маска поведения. Используется для определения типа поведения
	unsigned long	GetGroup();

	/// Возвращает сущность, которой управляет поведение
	EntityPtr			GetActor();

	/// Возвращает уровень на котором расположен объект
	LevelPtr			GetLevel();

	/// Обновить состояние повдения
	void			Update(float elapsedTime);

	/// Реализует собственно принятие решений объектом
	virtual void	Think(float elapsedTime) {}

	/// Обрабатывает столкновение с другим объектом. Вызывается во время ContactListener::PreSolve()
	virtual void	HandleContact(b2Contact* contact, const b2Manifold* oldMainfold, Entity* other) {}

	/// Включает и выключает поведение объекта
	virtual void	SetActive(bool value);

	/// Возвращает, активен ли объект
	bool			IsActive();

	/// Начать выполнениние действия
	void			StartAction(ActionPtr action);
protected:
	Behaviour();

	/// Устанавливает группу поведения
	void			SetGroup(unsigned long group);
private:
	/// Группа поведения
	unsigned long	mGroup;

	unsigned long	mActionMask;

	/// Список активных действий
	ActionList		mActiveActions;

	/// Сущность
	EntityWPtr			mActor;

	/// Флаг активности поведения
	bool			isActive;

	/// Устанавливает сущность, которой управляет поведение
	/// Метод вызывается автоматически
	void			SetActor(EntityPtr actor);

	/// Начинает
	//void			StartAction(ActionPtr parent, ActionPtr action);
protected:
	// Обновляет действия, выполняемые объектом
	void			UpdateActions(float elapsedTime);
	
};

/// class BehaviourDefinition
/// Определяет параметры поведения объекта
class BehaviourDefinition
{
public:
	BehaviourDefinition()
	{
	}

	virtual ~BehaviourDefinition()
	{
	}

	virtual void Parse(TiXmlElement* element) {}

	virtual BehaviourPtr Create() {return Behaviour::New();}
protected:
	std::string mType;
};

/// Интерфейс фабрики поведений
class IBehaviourFactory
{
public:
	virtual BehaviourDefPtr LoadDefinition(TiXmlElement* element) = 0;
};

template<class T>
class BehaviourFactory : public IBehaviourFactory
{
public:
	virtual BehaviourDefPtr LoadDefinition(TiXmlElement* element)
	{
		T* def = new T();
		def->Parse(element);

		return BehaviourDefPtr(def);
	}
};

typedef std::map<std::string, IBehaviourFactory*> BehaviourMap;

#endif
