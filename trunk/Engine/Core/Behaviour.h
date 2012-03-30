#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "Definitions.h"
#include "Collisions.h"
#include "Entity.h"

/// class Behaviour
/// Класс описывает поведение игрового объекта,
class ISILME_API Behaviour : public boost::enable_shared_from_this<Behaviour>
{
	friend class Entity;
	friend class FactoryManager;
	friend class EntityPalette;
public:
	static BehaviourPtr New();

	Behaviour();
	virtual ~Behaviour();

	/// Возвращает сущность, которой управляет поведение
	EntityPtr			GetActor();

	/// Gets entity that owns behaviour
	///
	/// @return entity
	EntityPtr		GetEntity();

	/// Возвращает уровень на котором расположен объект
	LevelPtr			GetLevel();

	/// Updates behaviour each iteration
	void			Update(float elapsedTime);

	/// Implements logic
	virtual void	OnUpdate(float elapsedTime) {}

	/// Обрабатывает столкновение с другим объектом. Вызывается во время ContactListener::PreSolve()
	virtual void	HandleContact(b2Contact* contact, const b2Manifold* oldMainfold, Entity* other) {}

	/// Включает и выключает поведение объекта
	virtual void	SetActive(bool value);

	/// Возвращает, активен ли объект
	bool			IsActive();

	/// Начать выполнениние действия
	void			StartAction(ActionPtr action);

	/// Terminates all active actions
	void			StopAllActions();

	/// Customizes.
	/// 
	/// @param [in]	element	If non-null, the element.
	/// @depricated
	virtual void	Customize(TiXmlElement* element);

	/// Gets number of active actions
	///
	/// @return numer of active actions
	int GetActiveActionsCount() const;
protected:
	/// @depricated
	Behaviour(BehaviourDefinition* def);
private:
	
	/// Active actions
	ActionList		mActiveActions;

	/// Weak reference to the owner
	EntityWPtr			mActor;

	/// Is behaviour active
	bool			isActive;

	/// Устанавливает сущность, которой управляет поведение
	/// Метод вызывается автоматически
	/// @depricated
	void			SetActor(EntityPtr actor);

	/// Начинает
	//void			StartAction(ActionPtr parent, ActionPtr action);
protected:
	/// Calls update for all active actions
	void			UpdateActions(float elapsedTime);
	
};

/// class BehaviourDefinition
/// Определяет параметры поведения объекта
class ISILME_API BehaviourDefinition
{
public:
	BehaviourDefinition()
	{
	}

	virtual ~BehaviourDefinition()
	{
	}

	virtual void Parse(TiXmlElement* element);

	virtual BehaviourPtr Create() {return Behaviour::New();}

	StringList AIPackages;
protected:
	/// Behaviour type
	std::string mType;


};

/// Интерфейс фабрики поведений
class IBehaviourFactory
{
public:
	virtual BehaviourDefPtr LoadDefinition(TiXmlElement* element) = 0;
};

typedef boost::shared_ptr<IBehaviourFactory> BehaviourFactoryPtr;

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

	static BehaviourFactoryPtr New()
	{
		return BehaviourFactoryPtr(new BehaviourFactory<T>());
	}
};

#endif
