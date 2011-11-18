#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <string>
#include <tinyxml.h>
#include "Definitions.h"
#include "Collisions.h"
#include "Entity.h"

/// class Behaviour
/// Класс описывает поведение игрового объекта,
class IsilmeExport Behaviour : public boost::enable_shared_from_this<Behaviour>
{
	friend class Entity;
	friend class FactoryManager;
public:
	static BehaviourPtr New();

	virtual ~Behaviour();

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

	/// Добавляет действие как состояние конечного автомата
	void			AddState(int stateID, ActionPtr action);

	/// Возвращает состояние конечного автомата
	bool			InState(int stateID);

	/// Устанавливает возможность перехода в состояние
	void			SetSwitchEnabled(int fromStateID, int toStateID, bool isEnabled);

	/// Перевести конечный автомат в указанное состояние
	void			SetState(int stateID);

	/// Разрешить или запретить параллельное выполнение действий (например идти и стрелять)
	void			SetParallelEnabled(int stateID, int otherStateID, bool isEnabled);

	/// Устанавливает значение аттрибута
	void			SetAttribute(std::string ID, float value);

	/// Возвращает значение аттрибута
	float			GetAttribute(std::string);

	void			AddAIPackage(AIPackagePtr package, int priority = 0);

	void			AddAIPackage(std::string packageID, int priority = 0);

	/// Customizes.
	/// 
	/// @param [in]	element	If non-null, the element.
	virtual void	Customize(TiXmlElement* element);
protected:
	Behaviour(BehaviourDefinition* def);
private:
	typedef std::pair<int, int> StatePair;
	typedef std::map<StatePair, bool>	StateRelationsMap;
	typedef std::map<int, ActionPtr> StateMap;
	typedef std::set<int> StateSet;
	typedef std::map<std::string, float> FloatMap;

	/// Атрибуты агента
	FloatMap	mAttributes;
	
	/// Текущие состояния
	StateSet	mCurrentStates;

	/// Карта состояний состояние-действий
	StateMap	mStatesMap;

	/// Карта переходов
	StateRelationsMap mSwitchMap;

	/// Карта параллельных состояний
	StateRelationsMap mParallelMap;
	
	/// Список активных действий
	ActionList		mActiveActions;

	/// Активные пакеты ИИ
	AIPackageList	mActivePackages;

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
class IsilmeExport BehaviourDefinition
{
public:
	BehaviourDefinition()
	{
	}

	virtual ~BehaviourDefinition()
	{
	}

	virtual void Parse(TiXmlElement* element);

	/// Считывает список аттрибутов
	void	ParseAttributes(TiXmlElement* attributesElement);

	/// Считывает описание ИИ
	void	ParseAIPackages(TiXmlElement* aiElement);

	virtual BehaviourPtr Create() {return Behaviour::New();}

	StringList AIPackages;

	AttributeMap Attributes;
protected:
	std::string mType;
};

/// Интерфейс фабрики поведений
class IBehaviourFactory
{
public:
	virtual BehaviourDefPtr LoadDefinition(TiXmlElement* element) = 0;
};

template<class T = BehaviourDefinition>
class BehaviourFactory : public IBehaviourFactory
{
public:
	virtual BehaviourDefPtr LoadDefinition(TiXmlElement* element)
	{
		T* def = new T();
		if (element)
			def->Parse(element);

		return BehaviourDefPtr(def);
	}
};

typedef std::map<std::string, IBehaviourFactory*> BehaviourMap;

#endif
