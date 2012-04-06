//  Copyright (C) 2010-2012 Alexander Alimov
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
